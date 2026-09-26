#pragma once

#include "Point.h"

#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& points) : m_Vertices(points) {}

    std::vector<Vertex> LocalToWorld() const;

    std::vector<Vertex>& GetVertices() { return m_Vertices; }
    const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
public:
    glm::vec3 position{};
    glm::vec3 rotation{};
    glm::vec3 scale{ 1.0f };
private:
    std::vector<Vertex> m_Vertices;
};