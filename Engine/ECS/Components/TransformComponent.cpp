#include "TransformComponent.h"

#include <glm/gtc/quaternion.hpp>

TransformComponent::TransformComponent(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
    position = pos;
    rotation = rot;
    this->scale = scale;
    
    UpdateData();
    UpdateAxisVectors();
}

void TransformComponent::UpdateData()
{
    transformMatrix = glm::mat4(1.0f);
    
    transformMatrix = glm::translate(transformMatrix, position); // Location
    
    // Rotation
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0)); 
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    
    transformMatrix = glm::scale(transformMatrix, scale); // Scale
}

void TransformComponent::UpdateAxisVectors()
{
    forward.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    forward.y = sin(glm::radians(rotation.x));
    forward.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    
    right = glm::cross(forward, glm::vec3(0, 1, 0));
    
    up = glm::cross(right, forward);
}

void TransformComponent::SetPosition(glm::vec3 value)
{
    position = value;
    UpdateData();
}

void TransformComponent::Translate(glm::vec3 value)
{
    SetPosition(position + value);
}

void TransformComponent::SetScale(glm::vec3 value)
{
    scale = value;
    UpdateData();
}

void TransformComponent::SetScale(float uniformScale)
{
    SetScale(glm::vec3(uniformScale));
}

void TransformComponent::SetRotation(glm::vec3 value)
{
    rotation = value;
    UpdateData();
    UpdateAxisVectors();
}

void TransformComponent::Rotate(glm::vec3 value)
{
    SetRotation(rotation + value);
}

void TransformComponent::PointAt(glm::vec3 targetPosition)
{
    if (targetPosition == position)
        return;
    
    
    glm::vec3 forwardVector = glm::normalize(targetPosition - position);
    SetRotation(eulerAngles(glm::quatLookAt(forwardVector, glm::vec3(0, 1, 0))) * (180.0f/glm::pi<float>()));
}

std::string TransformComponent::FetchSaveInfo()
{
    return std::format("{}, {}, {}, "
                       "{}, {}, {}, "
                       "{}, {}, {}",
                       position.x, position.y, position.z,
                       rotation.x, rotation.y, rotation.z,
                       scale.x, scale.y, scale.z);
}
