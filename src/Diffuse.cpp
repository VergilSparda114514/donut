#include "Diffuse.h"

Diffuse::Diffuse(const glm::vec3& sunDirection, ftxui::Color color) : m_SunDirection(glm::normalize(sunDirection)), m_Color(color)
{
}

ftxui::Cell Diffuse::Exec(const Vertex& point)
{
    std::string luminance = ".,-~:;=!*#$@";

    float light = glm::max(glm::dot(point.normal, m_SunDirection), 0.0f);

    ftxui::Cell cell{};
    cell.foreground_color = m_Color;
    cell.character = luminance[static_cast<size_t>(luminance.size() * light)];

    return cell;
}