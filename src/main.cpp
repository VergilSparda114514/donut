#include "Renderer.h"

#include "BlinnPhong.h"
#include "PixelShade.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/constants.hpp>

#include <numeric>
#include <algorithm>
#include <optional>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/ioctl.h>
#endif

static constexpr int ringCount = 100;
static constexpr int layerCount = 100;

static constexpr float radiusMajor = 1.0f;
static constexpr float radiusMinor = 0.25f;

static void push_args(int* argc, const char*** argv)
{
    (*argc)--;
    (*argv)++;
}

template <typename T>
static std::optional<T> parse_arg(const char* argStr, const std::string& key)
{
    std::optional<T> result = std::nullopt;
    std::string arg = argStr;

    std::transform(arg.begin(), arg.end(), arg.begin(), std::tolower);

    if (auto it = arg.find(key); it != std::string::npos)
    {
        try
        {
            result = T(arg.substr(it + key.length()));
        } catch(...) {}
    }

    return result;
}

template <>
std::optional<int> parse_arg(const char* argStr, const std::string& key)
{
    std::optional<int> num = std::nullopt;
    std::string arg = argStr;

    std::transform(arg.begin(), arg.end(), arg.begin(), std::tolower);

    if (auto it = arg.find(key); it != std::string::npos)
    {
        try
        {
            num = std::stoi(arg.substr(it + key.length()));
        } catch(...) {}
    }

    return num;
}

int main(int argc, const char* argv[])
{
    push_args(&argc, &argv);

    uint32_t width = 60;
    uint32_t height = 30;
    uint32_t fps = 30;
    bool complexShader = true;
    
    for (int i = 0; i < argc; i++)
    {
        width = parse_arg<int>(argv[i], "-w=").value_or(width);
        height = parse_arg<int>(argv[i], "-w=").value_or(height);
        fps = parse_arg<int>(argv[i], "-w=").value_or(fps);
        
        if (auto s = parse_arg<std::string>(argv[i], "-shd="); s.has_value())
        {
            complexShader = std::tolower((*s)[0]) == 'y';
        }
    }

#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi{};

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        uint32_t x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        uint32_t y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        
        width = std::clamp(width, 0u, x);
        height = std::clamp(height, 0u, y);
    }

    fps = max(fps, 1);
#else
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    
    width = std::clamp(width, 0u, static_cast<uint32_t>(ws.ws_row));
    height = std::clamp(height, 0u, static_cast<uint32_t>(ws.ws_col));

    fps = std::max(fps, 1u);
#endif

    Renderer renderer{ width, height, fps };
    Camera& camera = renderer.GetCamera();

    std::vector<Vertex> vertices(ringCount * layerCount);
    
    for (int i = 0; i < ringCount; i++)
    {   
        for (int j = 0; j < layerCount; j++)
        {
            float theta = 2.0f * glm::pi<float>() * i / ringCount;
            float phi = 2.0f * glm::pi<float>() * j / layerCount;

            glm::vec3 position{};
            position.x = (radiusMajor + radiusMinor * glm::cos(phi)) * glm::cos(theta);
            position.y = radiusMinor * glm::sin(phi);
            position.z = (radiusMajor + radiusMinor * glm::cos(phi)) * glm::sin(theta);

            glm::vec3 normal{};
            normal.x = glm::cos(phi) * glm::cos(theta);
            normal.y = glm::sin(phi);
            normal.z = glm::cos(phi) * glm::sin(theta);

            vertices[j + i * layerCount].position = position;
            vertices[j + i * layerCount].normal = normal;
        }
    }

    Mesh mesh{ vertices };
    mesh.position = { 0.0f, 0.0f, 2.0f };

    std::unique_ptr<Shader> shader = std::make_unique<PixelShade>();

    std::unique_ptr<BlinnPhong> brdf = std::make_unique<BlinnPhong>(camera);
    brdf->diffuseColor = glm::vec3(1.0f, 0.0f, 0.0f);
    brdf->specularColor = glm::vec3(1.0f);
    brdf->specular = 16.0f;

    if (complexShader)
    {
        shader = std::move(brdf);
    }

    renderer.BindShader(std::move(shader));

    while (true)
    {
        mesh.rotation.x += 45.0f * renderer.DeltaTime();
        mesh.rotation.y += 90.0f * renderer.DeltaTime();

        renderer.DrawMesh(mesh);
        renderer.Render();
    }
}