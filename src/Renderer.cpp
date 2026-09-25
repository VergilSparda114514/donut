#include "Renderer.h"

#include <iostream>

static std::string luminance = ".,-~:;=!*#$@";

static glm::vec3 sunDirection = glm::normalize(glm::vec3(-1, 1, -1));

void Renderer::DrawPoint(const Point& point)
{
    glm::vec2 screenCoord = m_Camera.WorldToScreen(point.position);
    glm::vec2 normalizedCoord = (screenCoord + 1.0f) * 0.5f;
    glm::uvec2 pixelCoord((Width() - 1) * normalizedCoord.x, (Height() - 1) * (1.0f - normalizedCoord.y));

    if (pixelCoord.x < 0 || pixelCoord.x >= Width() || pixelCoord.y < 0 || pixelCoord.y >= Height())
    {
        return;
    }

    float light = glm::max(glm::dot(point.normal, sunDirection), 0.0f);
    
    ftxui::Cell cell{};
    cell.character = luminance[static_cast<size_t>(luminance.size() * light)];

    float d = 1.0f / point.position.z;

    if (d > m_DepthBuffer[pixelCoord.x + pixelCoord.y * Width()])
    {
        m_DepthBuffer[pixelCoord.x + pixelCoord.y * Width()] = d;
        m_Screen.CellAt(pixelCoord.x, pixelCoord.y) = cell;
    }
}

void Renderer::DrawMesh(const Mesh& mesh)
{
    for (const auto& point : mesh.LocalToWorld())
    {
        DrawPoint(point);
    }
}

void Renderer::Render()
{
    std::cout << m_Screen.ResetPosition();
    m_Screen.Print();

    for (size_t y = 0; y < Height(); y++)
    {
        for (size_t x = 0; x < Width(); x++)
        {
            m_Screen.CellAt(x, y) = ftxui::Cell{};
            m_DepthBuffer[x + y * Width()] = 0.0f;
        }
    }
}