#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

struct TransformComponent
{
    TransformComponent() = default;
    
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    
    glm::mat4 GetTransformMatrix()
    {
        glm::mat4 transformMatrix = glm::mat4(1.0f);
    
        transformMatrix = glm::translate(transformMatrix, position); // Location
    
        // Rotation
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0)); 
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    
        transformMatrix = glm::scale(transformMatrix, scale); // Scale
        
        return transformMatrix;
    }
};
