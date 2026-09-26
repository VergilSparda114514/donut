#include "Diffuse.h"

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_LEFT_HANDED

Diffuse::Diffuse(const glm::vec3& sunDirection) : m_SunDirection(glm::normalize(sunDirection))
{
}

ftxui::Cell Diffuse::Exec(const Vertex& point)
{
    std::string luminance = ".,-~:;=!*#$@";

    float light = glm::max(glm::dot(point.normal, m_SunDirection), 0.0f);

    ftxui::Cell cell{};
    cell.foreground_color = ftxui::Color(point.color.x * 255, point.color.y * 255, point.color.z * 255);
    cell.character = luminance[static_cast<size_t>(luminance.size() * light)];

    return cell;
}