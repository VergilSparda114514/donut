#include "Camera.h"

glm::vec2 Camera::WorldToScreen(const glm::vec3& worldPos)
{
    glm::vec2 coord{};

    coord.x = m_NearPlane * worldPos.x / worldPos.z;
    coord.y = m_NearPlane * worldPos.y / worldPos.z;

    return coord;
}