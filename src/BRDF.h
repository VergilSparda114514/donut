#pragma once

#include "Shader.h"
#include "Camera.h"

class BRDF : public Shader
{
public:
    BRDF(const Camera& camera) : m_Camera(camera) {}

    virtual ftxui::Cell Exec(const Vertex& point) override;
public:
    glm::vec3 baseColor{ 0.04f };

    float metallic = 0.0f;
    float roughness = 0.0f;
    float specular = 0.0f;
private:
    const Camera& m_Camera;
};