#pragma once

#include "Point.h"

#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<Point>& points) : m_Points(points) {}

    std::vector<Point> LocalToWorld() const;

    std::vector<Point>& GetPoints() { return m_Points; }
    const std::vector<Point>& GetPoints() const { return m_Points; }
public:
    glm::vec3 position{};
    glm::vec3 rotation{};
    glm::vec3 scale{ 1.0f };
private:
    std::vector<Point> m_Points;
};