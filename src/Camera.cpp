#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

glm::vec2 Camera::WorldToScreen(const glm::vec3& worldPos) const
{
    glm::vec3 localPos = WorldToLocal(worldPos);

    glm::vec2 screenCoord{};
    screenCoord.x = localPos.x / localPos.z;
    screenCoord.y = localPos.y / localPos.z;

    return screenCoord;
}

glm::vec3 Camera::WorldToLocal(const glm::vec3& worldPos) const
{
    glm::vec3 localPos = worldPos - position;
    localPos = glm::angleAxis(glm::radians(-rotation.x), glm::vec3(1, 0, 0)) * localPos;
    localPos = glm::angleAxis(glm::radians(-rotation.y), glm::vec3(0, 1, 0)) * localPos;
    localPos = glm::angleAxis(glm::radians(-rotation.z), glm::vec3(0, 0, 1)) * localPos;

    return localPos;
}