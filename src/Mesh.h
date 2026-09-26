#pragma once

#include "Point.h"

#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& points) : m_Points(points) {}

    std::vector<Vertex> LocalToWorld() const;

    std::vector<Vertex>& GetPoints() { return m_Points; }
    const std::vector<Vertex>& GetPoints() const { return m_Points; }
public:
    glm::vec3 position{};
    glm::vec3 rotation{};
    glm::vec3 scale{ 1.0f };
private:
    std::vector<Vertex> m_Points;
};