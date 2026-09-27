#include "PixelShade.h"

static std::string luminance = ".,-~:;=!*#$@";
static glm::vec3 lightDirection = glm::normalize(glm::vec3(-1, 1, -1));

ftxui::Cell PixelShade::frag(const Vertex& vertex)
{
    float cosTheta = glm::max(glm::dot(vertex.normal, lightDirection), 0.0f);

    ftxui::Cell cell{};
    cell.character = luminance[static_cast<size_t>(luminance.size() * cosTheta)];

    return cell;
}