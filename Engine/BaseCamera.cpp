#include "BaseCamera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "InputManager.h"
#include "MouseEngineContext.h"

glm::mat4 BaseCamera::GetView() const
{
    // glm::vec3 rotation = transform.GetRotation();
    // glm::vec3 direction;
    // direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    // direction.y = sin(glm::radians(rotation.x));
    // direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    
    glm::vec3 pos2 = transform.GetPosition();
    return glm::lookAt(pos2, pos2 + transform.GetForward(), glm::vec3(0, 1, 0));
}

glm::mat4 BaseCamera::GetProjection() const
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void BaseCamera::SetAspectRatio(float ratio)
{
    aspectRatio = ratio;
}

void BaseCamera::Process(float deltaTime)
{
    glm::vec3 move = glm::vec3(0.0f);
    if (EngineContext->Input->IsKeyPressedDown(GLFW_KEY_W))
        move.z += 1.0f;
    if (EngineContext->Input->IsKeyPressedDown(GLFW_KEY_S))
        move.z -= 1.0f;
    if (EngineContext->Input->IsKeyPressedDown(GLFW_KEY_D))
        move.x += 1.0f;
    if (EngineContext->Input->IsKeyPressedDown(GLFW_KEY_A))
        move.x -= 1.0f;
    if (EngineContext->Input->IsKeyPressedDown(GLFW_KEY_SPACE))
        move.y += 1.0f;
    if (EngineContext->Input->IsKeyPressedDown(GLFW_KEY_LEFT_CONTROL))
        move.y -= 1.0f;
    
    if (glm::length(move) < 0.01)
        return;
    
    const float speed = 10.0f;
    
    glm::vec3 moveVector = glm::vec3(0.0f);
    moveVector += move.x * transform.GetRight();
    moveVector += move.y * transform.GetUp();
    moveVector += move.z * transform.GetForward();
    
    moveVector = glm::normalize(moveVector);
    
    transform.Translate(moveVector * speed * deltaTime);
}
