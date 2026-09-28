#pragma once

#include <ftxui/screen/screen.hpp>

#include <glm/glm.hpp>

#include <vector>
#include <memory>

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"

class Renderer
{
public:
    Renderer(uint32_t width = 80, uint32_t height = 40, uint32_t targetFPS = 30);

    void BindShader(std::unique_ptr<Shader> shader);
    void DrawVertex(const Vertex& point);
    void DrawMesh(const Mesh& mesh);
    void Render();

    Camera& GetCamera() { return m_Camera; }
    const Camera& GetCamera() const { return m_Camera; }

    void SetBorder(bool border);

    constexpr uint32_t Width() const { return m_Width; }
    constexpr uint32_t Height() const { return m_Height; }
    constexpr float DeltaTime() const { return m_DeltaTime; }
private:
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
    uint32_t m_TargetFPS = 0;
    float m_AspectRatio = 0.0f;
    float m_DeltaTime = 0.0f;
    bool m_EnableBorder = true;

    ftxui::Screen m_Screen;
    std::vector<float> m_DepthBuffer;

    Camera m_Camera{};
    std::unique_ptr<Shader> m_Shader = nullptr;
};