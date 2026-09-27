#pragma once

#include "Shader.h"
#include "Camera.h"

class BlinnPhong : public Shader
{
public:
    BlinnPhong(const Camera& camera) : m_Camera(camera) {}

    virtual ftxui::Cell Exec(const Vertex& vertex) override;
public:
    glm::vec3 diffuseColor{ 1.0f };
    glm::vec3 specularColor{ 1.0f };
    
    float specular = 0.0f;
private:
    const Camera& m_Camera;
};