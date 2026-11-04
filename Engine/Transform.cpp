#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>

Transform::Transform()
{
    UpdateData();
    UpdateAxisVectors();
}

void Transform::UpdateData()
{
    transformMatrix = glm::mat4(1.0f);
    
    transformMatrix = glm::translate(transformMatrix, position); // Location
    
    // Rotation
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0)); 
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    
    transformMatrix = glm::scale(transformMatrix, scale); // Scale
}

void Transform::UpdateAxisVectors()
{
    forward.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    forward.y = sin(glm::radians(rotation.x));
    forward.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    
    right = glm::cross(forward, glm::vec3(0, 1, 0));
    
    up = glm::cross(right, forward);
}

void Transform::SetPosition(glm::vec3 value)
{
    position = value;
    UpdateData();
}

void Transform::Translate(glm::vec3 value)
{
    SetPosition(position + value);
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
    UpdateAxisVectors();
}

void Transform::Rotate(glm::vec3 value)
{
    SetRotation(rotation + value);
}
