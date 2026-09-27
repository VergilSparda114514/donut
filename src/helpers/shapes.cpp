#include "shapes.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/constants.hpp>

#include <vector>

namespace shapes
{
    Mesh Torus(float radiusMajor, float radiusMinor, uint32_t numRings, uint32_t numLayers)
    {
        std::vector<Vertex> vertices(numRings * numLayers);
        
        for (int i = 0; i < numRings; i++)
        {   
            for (int j = 0; j < numLayers; j++)
            {
                float theta = glm::two_pi<float>() * i / numRings;
                float phi = glm::two_pi<float>() * j / numLayers;

                glm::vec3 position{};
                position.x = (radiusMajor + radiusMinor * glm::cos(phi)) * glm::cos(theta);
                position.y = radiusMinor * glm::sin(phi);
                position.z = (radiusMajor + radiusMinor * glm::cos(phi)) * glm::sin(theta);

                glm::vec3 normal{};
                normal.x = glm::cos(phi) * glm::cos(theta);
                normal.y = glm::sin(phi);
                normal.z = glm::cos(phi) * glm::sin(theta);

                vertices[j + i * numLayers].position = position;
                vertices[j + i * numLayers].normal = normal;
            }
        }

        return { vertices };
    }

    Mesh Sphere(float radius, uint32_t numRings, uint32_t numLayers)
    {
        std::vector<Vertex> vertices(numRings * numLayers);

        for (int i = 0; i < numLayers; i++)
        {
            for (int j = 0; j < numRings; j++)
            {
                float theta = glm::two_pi<float>() * j / numRings;
                float phi = glm::pi<float>() * i / numLayers;

                glm::vec3 direction{};
                direction.x = glm::sin(phi) * glm::cos(theta);
                direction.y = glm::cos(phi);
                direction.z = glm::sin(phi) * glm::sin(theta);

                vertices[j + i * numRings].position = direction * radius;
                vertices[j + i * numRings].normal = direction;
            }
        }

        return { vertices }; 
    }
}