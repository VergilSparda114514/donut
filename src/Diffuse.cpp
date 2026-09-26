#include "Diffuse.h"

ftxui::Cell Diffuse::Exec(const Vertex& point)
{
    std::string luminance = ".,-~:;=!*#$@";

    float light = glm::max(glm::dot(point.normal, m_SunDirection), 0.0f);
    glm::vec3 color = glm::pow(point.color * light, glm::vec3(1.0f / 2.2f));

    ftxui::Cell cell{};
    cell.foreground_color = ftxui::Color(color.x * 255, color.y * 255, color.z * 255);
    cell.character = luminance[static_cast<size_t>(luminance.size() * light)];

    return cell;
}