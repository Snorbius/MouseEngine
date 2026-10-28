#include "AssessmentHouse.h"

#include <numbers>

#include "../Shader.h"

void AssessmentHouse::DrawTriangle(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, glm::vec4 color, Shader* shader)
{
    triangleMesh.transform.SetPosition(pos);
    triangleMesh.transform.SetScale(scale);
    triangleMesh.transform.SetRotation(rot);
    
    shader->Use();
    shader->SetUniform("u_color", color);
    triangleMesh.Render(shader);
}

void AssessmentHouse::DrawRectangle(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, glm::vec4 color, Shader* shader)
{
    DrawTriangle(pos, scale, rot, color, shader);
    DrawTriangle(pos, scale, rot + glm::vec3(std::numbers::pi_v<float>), color, shader);
}

void AssessmentHouse::Render(Shader* shader)
{
    glm::vec3 center = glm::vec3(0.0f, -0.2f, 0.0f);
    
    DrawRectangle(center + glm::vec3(0.0f), glm::vec3(0.65f, 0.5f, 1.0f), glm::vec3(0.0f), glm::vec4(0.565f, 0.275f, 0.812f, 1.0f), shader);
    DrawTriangle(center + glm::vec3(0.0f, 0.75f, 0.0f), glm::vec3(0.8f, 0.25f, 1.0f), glm::vec3(0.0f), roofColor, shader);
    DrawRectangle(center + glm::vec3(-0.35f, 0.1f, 0.0f), glm::vec3(0.12f), glm::vec3(powf(time * 0.35f, 3)), glm::vec4(0.957f, 0.529f, 0.714f, 1.0f), shader);
    DrawRectangle(center + glm::vec3(0.35f, 0.1f, 0.0f), glm::vec3(0.12f), glm::vec3(1.2f), glm::vec4(0.957f, 0.529f, 0.714f, 1.0f), shader);
    DrawRectangle(center + glm::vec3(0.0f, -0.34f, 0.0f), glm::vec3(0.08f, 0.16f, 1.0f), glm::vec3(0.0f), glm::vec4(0.8f, 0.349f, 0.824f, 1.0f), shader);
}

void AssessmentHouse::SwapRoofColor()
{
    roofswap = !roofswap;
    roofColor = roofswap ? glm::vec4(0.482f, 0.945f, 0.659f, 1.0f) : glm::vec4(0.992f, 0.882f, 0.176f, 1.0f);
}
