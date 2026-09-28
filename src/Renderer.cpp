#include "Renderer.h"

#include <ftxui/dom/elements.hpp>

#include <iostream>
#include <thread>
#include <chrono>

Renderer::Renderer(uint32_t width, uint32_t height, uint32_t targetFPS) :
    m_Width(width), m_Height(height), m_TargetFPS(targetFPS), m_AspectRatio(static_cast<float>(width) / static_cast<float>(height * 2)),
    m_Screen(ftxui::Screen::Create(ftxui::Dimension::Fixed(width), ftxui::Dimension::Fixed(height))), m_DepthBuffer(width * height), m_Camera(1.0f)
{
#ifndef __APPLE__
    m_AspectRatio *= 8.5f / 9.0f;
#endif
}

void Renderer::BindShader(std::unique_ptr<Shader> shader)
{
    m_Shader = std::move(shader);
}

void Renderer::DrawVertex(const Vertex& vertex)
{
    glm::vec2 screenCoord = m_Camera.WorldToScreen(vertex.position);
    screenCoord.y *= m_AspectRatio;

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
        m_Screen.CellAt(pixelCoord.x, pixelCoord.y) = m_Shader->frag(vertex);
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
    using namespace std::chrono;

    static time_point<high_resolution_clock> start = high_resolution_clock::now();
    time_point<high_resolution_clock> now = high_resolution_clock::now();

    m_DeltaTime = std::chrono::duration_cast<nanoseconds>(now - start).count() / static_cast<float>(nanoseconds::period::den);
    start = now;

    std::cout << m_Screen.ResetPosition();

    if (m_EnableBorder)
    {
        ftxui::Element border = ftxui::hbox({
            ftxui::text("") | ftxui::border | ftxui::flex
        });

        ftxui::Render(m_Screen, border);
    }

    m_Screen.Print();

    for (size_t y = 0; y < Height(); y++)
    {
        for (size_t x = 0; x < Width(); x++)
        {
            m_Screen.CellAt(x, y) = ftxui::Cell{};
            m_DepthBuffer[x + y * Width()] = 0.0f;
        }
    }

    if (m_TargetFPS > 0)
    {
        std::this_thread::sleep_for(nanoseconds(nanoseconds::period::den / m_TargetFPS));
    }
}

void Renderer::SetBorder(bool border)
{
    m_EnableBorder = border;
}