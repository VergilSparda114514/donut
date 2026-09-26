#include "Renderer.h"

#include <iostream>
#include <thread>

void Renderer::BindShader(std::unique_ptr<Shader> shader)
{
    m_Shader = std::move(shader);
}

void Renderer::DrawVertex(const Vertex& vertex)
{
    glm::vec2 screenCoord = m_Camera.WorldToScreen(vertex.position);

    if (screenCoord.x < -1.0f || screenCoord.x > 1.0f || screenCoord.y < -1.0f || screenCoord.y > 1.0f)
    {
        return;
    }

    glm::vec2 normalizedCoord = (screenCoord + 1.0f) * 0.5f;
    glm::uvec2 pixelCoord((Width() - 1) * normalizedCoord.x, (Height() - 1) * (1.0f - normalizedCoord.y));

    float d = 1.0f / vertex.position.z;

    if (d > m_DepthBuffer[pixelCoord.x + pixelCoord.y * Width()])
    {
        m_DepthBuffer[pixelCoord.x + pixelCoord.y * Width()] = d;
        m_Screen.CellAt(pixelCoord.x, pixelCoord.y) = m_Shader->Exec(vertex);
    }
}

void Renderer::DrawMesh(const Mesh& mesh)
{
    for (const auto& vertex : mesh.LocalToWorld())
    {
        DrawVertex(vertex);
    }
}

void Renderer::Render()
{
    std::cout << m_Screen.ResetPosition(true);
    m_Screen.Print();

    for (size_t y = 0; y < Height(); y++)
    {
        for (size_t x = 0; x < Width(); x++)
        {
            m_Screen.CellAt(x, y) = ftxui::Cell{};
            m_DepthBuffer[x + y * Width()] = 0.0f;
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / m_TargetFPS));
}

void Renderer::SetTargetFPS(uint32_t targetFPS)
{
    m_TargetFPS = targetFPS;
}