#include "BRDF.h"

#include <glm/gtc/constants.hpp>

static std::string luminance = ".,-~:;=!*#$@";
static glm::vec3 lightDirection = glm::vec3(-1, 1, -1);
static glm::vec3 lightColor = glm::vec3(10.0f);
static float epsilon = 1e-6;

static float D(float alpha, const glm::vec3& N, const glm::vec3& H)
{
    float num = alpha * alpha;

    float NdotH = glm::max(glm::dot(N, H), epsilon);
    float denom = glm::pi<float>() * glm::pow(NdotH * NdotH * (num - 1.0f) + 1.0f, 2.0f);

    return num / glm::max(denom, epsilon);
}

static float G1(float alpha, const glm::vec3& N, const glm::vec3& X)
{
    float num = glm::max(glm::dot(N, X), 0.0f);

    float k = alpha / 2.0f;
    float denom = num * (1.0f - k) + k;

    return num / glm::max(denom, epsilon);
}

static float G(float alpha, const glm::vec3& N, const glm::vec3& V, const glm::vec3& L)
{
    return G1(alpha, N, V) * G1(alpha, N, L);
}

static glm::vec3 F(const glm::vec3& F0, const glm::vec3& V, const glm::vec3& H)
{
    return F0 + (1.0f - F0) * glm::pow(1.0f - glm::max(glm::dot(V, H), 0.0f), 5.0f);
}

ftxui::Cell BRDF::Exec(const Vertex& vertex)
{
    glm::vec3 N = glm::normalize(vertex.normal);
    glm::vec3 V = glm::normalize(m_Camera.position - vertex.position);
    glm::vec3 L = glm::normalize(lightDirection);
    glm::vec3 H = glm::normalize(V + L);

    float alpha = roughness * roughness;
    float cosTheta = glm::max(glm::dot(L, N), 0.0f);
    glm::vec3 F0 = glm::mix(baseColor * specular, vertex.color, metallic);

    glm::vec3 ks = F(F0, V, H);
    glm::vec3 kd = (1.0f - ks) * (1.0f - metallic);

    glm::vec3 diffuse = vertex.color / glm::pi<float>();

    glm::vec3 num = D(alpha, N, H) * G(alpha, N, V, L) * ks;
    float denom = 4.0f * glm::max(glm::dot(V, N), 0.0f) * cosTheta;
    glm::vec3 cookTorrance = num / glm::max(denom, epsilon);

    glm::vec3 BRDF = kd * diffuse + cookTorrance;
    glm::vec3 throughput = BRDF * lightColor * cosTheta;

    glm::vec3 color = glm::clamp(glm::pow(throughput, glm::vec3(1.0f / 2.2f)), 0.0f, 1.0f);

    ftxui::Cell cell{};
    cell.foreground_color = ftxui::Color(color.x * 255, color.y * 255, color.z * 255);
    cell.character = luminance[static_cast<size_t>(luminance.size() * cosTheta)];

    return cell;
}