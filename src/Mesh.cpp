#include "Mesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

std::vector<Vertex> Mesh::LocalToWorld() const
{
    std::vector<Vertex> points(m_Vertices.size());

    for (size_t i = 0; i < m_Vertices.size(); i++)
    {
        points[i].position = (m_Vertices[i].position * scale);
        points[i].position = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1, 0, 0)) * points[i].position;
        points[i].position = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0, 1, 0)) * points[i].position;
        points[i].position = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0, 0, 1)) * points[i].position;
        points[i].position += position;

        points[i].normal = m_Vertices[i].normal;
        points[i].normal = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1, 0, 0)) * points[i].normal;
        points[i].normal = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0, 1, 0)) * points[i].normal;
        points[i].normal = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0, 0, 1)) * points[i].normal;

        points[i].color = m_Vertices[i].color;
    }

    return points;
}