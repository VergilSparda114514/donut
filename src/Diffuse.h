#pragma once

#include "Shader.h"

class Diffuse : public Shader
{
public:
    Diffuse(const glm::vec3& sunDirection);

    virtual ftxui::Cell Exec(const Vertex& point) override;
private:
    glm::vec3 m_SunDirection{};
};