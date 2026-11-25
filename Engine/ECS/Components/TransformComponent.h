#pragma once
#include <glm/vec3.hpp>

struct TransformComponent
{
    TransformComponent() = default;
    
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
};
