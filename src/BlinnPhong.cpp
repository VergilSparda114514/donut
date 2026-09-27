#include "BlinnPhong.h"

static std::string luminance = ".,-~:;=!*#$@";
static glm::vec3 lightDirection = glm::vec3(-1, 1, -1);
static glm::vec3 lightColor = glm::vec3(1.0f);

ftxui::Cell BlinnPhong::Exec(const Vertex& vertex)
{
    glm::vec3 N = glm::normalize(vertex.normal);
    glm::vec3 L = glm::normalize(lightDirection);
    glm::vec3 V = glm::normalize(m_Camera.position - vertex.position);
    glm::vec3 H = glm::normalize(V + L);

    float cosTheta = glm::max(glm::dot(N, L), 0.0f);
    float highlight = glm::pow(glm::max(glm::dot(N, H), 0.0f), specular);
    
    glm::vec3 blinnPhong = diffuseColor * cosTheta + specularColor * highlight;
    glm::vec3 throughput = blinnPhong * lightColor;
    glm::vec3 color = glm::clamp(glm::pow(throughput, glm::vec3(1.0f / 2.2f)), 0.0f, 1.0f);

    ftxui::Cell cell{};
    cell.foreground_color = ftxui::Color(color.r * 255, color.g * 255, color.b * 255);
    cell.character = luminance[static_cast<size_t>(luminance.size() * cosTheta)];

    return cell;
}