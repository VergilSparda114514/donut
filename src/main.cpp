#include "Renderer.h"
#include "Diffuse.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

static constexpr int ringCount = 100;
static constexpr int layerCount = 100;

static constexpr float radiusMajor = 1.0f;
static constexpr float radiusMinor = 0.25f;

int main()
{
    Renderer renderer{ 100, 50, 120 };
    Camera& camera = renderer.GetCamera();

    std::vector<Vertex> points(ringCount * layerCount);
    
    for (int i = 0; i < ringCount; i++)
    {   
        for (int j = 0; j < layerCount; j++)
        {
            float theta = 2.0f * M_PI * i / ringCount;
            float phi = 2.0f * M_PI * j / layerCount;

            glm::vec3 position{};
            position.x = (radiusMajor + radiusMinor * glm::cos(phi)) * glm::cos(theta);
            position.y = radiusMinor * glm::sin(phi);
            position.z = (radiusMajor + radiusMinor * glm::cos(phi)) * glm::sin(theta);

            glm::vec3 normal{};
            normal.x = glm::cos(phi) * glm::cos(theta);
            normal.y = glm::sin(phi);
            normal.z = glm::cos(phi) * glm::sin(theta);

            points[j + i * layerCount].position = position;
            points[j + i * layerCount].normal = normal;
        }
    }

    Mesh mesh{ points };
    mesh.position = { 0.0f, 0.0f, 2.0f };

    renderer.BindShader(std::make_unique<Diffuse>(glm::vec3(-1, 1, -1)));

    while (true)
    {
        mesh.rotation.x += 45.0f * renderer.DeltaTime();
        mesh.rotation.y += 90.0f * renderer.DeltaTime();

        renderer.DrawMesh(mesh);
        renderer.Render();
    }
}