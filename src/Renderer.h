#pragma once

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <glm/glm.hpp>
#include <vector>

#include "Camera.h"
#include "Mesh.h"

class Renderer
{
public:
    Renderer(uint32_t width = 80, uint32_t height = 40) : m_Width(width), m_Height(height),
        m_Screen(ftxui::Screen::Create(ftxui::Dimension::Fixed(width), ftxui::Dimension::Fixed(height))), m_DepthBuffer(width * height) {}

    void DrawPoint(const Point& point);
    void DrawMesh(const Mesh& mesh);
    void Render();

    constexpr uint32_t Width() const { return m_Width; }
    constexpr uint32_t Height() const { return m_Height; }
private:
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;

    ftxui::Screen m_Screen;
    std::vector<float> m_DepthBuffer;

    Camera m_Camera{};
};