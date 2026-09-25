#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(float nearPlane = 1.0f) : m_NearPlane(nearPlane) {}
    
    glm::vec2 WorldToScreen(const glm::vec3& worldPos);
private:
    float m_NearPlane = 1.0f;
};