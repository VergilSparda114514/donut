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
    Renderer(int width = 80, int height = 40, int targetFPS = 30);

    void BindShader(std::unique_ptr<Shader> shader);
    void DrawVertex(const Vertex& point);
    void DrawMesh(const Mesh& mesh);
    void Render();

    Camera& GetCamera() { return m_Camera; }
    const Camera& GetCamera() const { return m_Camera; }

    void SetBorder(bool border);

    constexpr int Width() const { return m_Width; }
    constexpr int Height() const { return m_Height; }
    constexpr float DeltaTime() const { return m_DeltaTime; }
private:
    int m_Width = 0;
    int m_Height = 0;
    int m_TargetFPS = 0;
    float m_AspectRatio = 0.0f;
    float m_DeltaTime = 0.0f;
    bool m_EnableBorder = true;

    ftxui::Screen m_Screen;
    std::vector<float> m_DepthBuffer;

    Camera m_Camera{};
    std::unique_ptr<Shader> m_Shader = nullptr;
};