#include "Renderer.h"

#include "BlinnPhong.h"
#include "PixelShade.h"

#include "helpers/args.h"
#include "helpers/terminal.h"
#include "helpers/shapes.h"

int main(int argc, const char* argv[])
{
    args::push(&argc, &argv);

    uint32_t width = 60;
    uint32_t height = 30;
    uint32_t fps = 30;
    bool complexShader = true;
    bool border = true;
    
    for (int i = 0; i < argc; i++)
    {
        width = args::parse<int>(argv[i], "-w=").value_or(width);
        height = args::parse<int>(argv[i], "-h=").value_or(height);
        fps = args::parse<int>(argv[i], "-fps=").value_or(fps);
        
        if (auto s = args::parse<std::string>(argv[i], "-shd="); s.has_value())
        {
            complexShader = std::tolower((*s)[0]) == 'y';
        }
        
        if (auto s = args::parse<std::string>(argv[i], "-brd="); s.has_value())
        {
            border = std::tolower((*s)[0]) == 'y';
        }
    }
    
    auto [twidth, theight] = terminal::GetDimensions();

    width = std::clamp(width, 0u, twidth);
    height = std::clamp(height, 0u, theight);
    fps = std::max(fps, 0u);

    if (width == 0)
    {
        width = twidth;
    }

    if (height == 0)
    {
        height = theight;
    }

    Renderer renderer{ width, height, fps };
    Camera& camera = renderer.GetCamera();

    renderer.SetBorder(border);

    Mesh donut = shapes::Torus(1.0f, 0.25f, 100, 100);
    donut.position = { -2.5f, 0.0f, 5.0f };

    Mesh ball = shapes::Sphere(1.0f, 100, 100);
    ball.position = { 2.5f, 0.0f, 5.0f };

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
        donut.rotation.x += 45.0f * renderer.DeltaTime();
        donut.rotation.y += 90.0f * renderer.DeltaTime();

        renderer.DrawMesh(donut);
        renderer.DrawMesh(ball);
        renderer.Render();
    }
}