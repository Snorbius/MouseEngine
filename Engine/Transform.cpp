#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>

Transform::Transform()
{
    UpdateData();
}

void Transform::UpdateData()
{
    transformMatrix = glm::mat4(1.0f);
    
    transformMatrix = glm::translate(transformMatrix, position); // Location
    
    // Rotation
    transformMatrix = glm::rotate(transformMatrix, rotation.x, glm::vec3(1, 0, 0)); 
    transformMatrix = glm::rotate(transformMatrix, rotation.y, glm::vec3(0, 1, 0));
    transformMatrix = glm::rotate(transformMatrix, rotation.z, glm::vec3(0, 0, 1));
    
    transformMatrix = glm::scale(transformMatrix, scale); // Scale
}

void Transform::SetPosition(glm::vec3 value)
{
    position = value;
    UpdateData();
}

void Transform::SetScale(glm::vec3 value)
{
    scale = value;
    UpdateData();
}

void Transform::SetRotation(glm::vec3 value)
{
    rotation = value;
    UpdateData();
}
