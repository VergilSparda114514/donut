#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(float nearPlane = 1.0f) : m_NearPlane(nearPlane) {}

    glm::vec2 WorldToScreen(const glm::vec3& worldPos) const;
private:
    glm::vec3 WorldToLocal(const glm::vec3& worldPos) const;
public:
    glm::vec3 position{};
    glm::vec3 rotation{};
private:
    float m_NearPlane = 1.0f;
};