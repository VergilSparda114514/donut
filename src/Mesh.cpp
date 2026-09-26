#include "Mesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

std::vector<Vertex> Mesh::LocalToWorld() const
{
    std::vector<Vertex> vertices(m_Vertices.size());

    for (size_t i = 0; i < m_Vertices.size(); i++)
    {
        vertices[i].position = m_Vertices[i].position * scale;
        vertices[i].position = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1, 0, 0)) * vertices[i].position;
        vertices[i].position = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0, 1, 0)) * vertices[i].position;
        vertices[i].position = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0, 0, 1)) * vertices[i].position;
        vertices[i].position += position;

        vertices[i].normal = m_Vertices[i].normal;
        vertices[i].normal = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1, 0, 0)) * vertices[i].normal;
        vertices[i].normal = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0, 1, 0)) * vertices[i].normal;
        vertices[i].normal = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0, 0, 1)) * vertices[i].normal;

        vertices[i].color = m_Vertices[i].color;
    }

    return vertices;
}