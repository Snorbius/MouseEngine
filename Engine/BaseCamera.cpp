#include "BaseCamera.h"

#include <format>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "InputManager.h"
#include "MouseEngineContext.h"

BaseCamera::BaseCamera()
{
    EngineContext->RegisterForInput(this);
}

glm::mat4 BaseCamera::GetView() const
{
    glm::vec3 pos2 = transform.GetPosition();
    return glm::lookAt(pos2, pos2 + transform.GetForward(), glm::vec3(0, 1, 0));
}

glm::mat4 BaseCamera::GetProjection() const
{
    const float orthosize = 6;

    return
        orthographic
            ? glm::ortho(-orthosize * aspectRatio, orthosize * aspectRatio, -orthosize, orthosize, nearPlane, farPlane)
            : glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void BaseCamera::SetIsOrthographic(bool value)
{
    orthographic = value;
}

void BaseCamera::SetAspectRatio(float ratio)
{
    aspectRatio = ratio;
}

void BaseCamera::HandleMovement(float deltaTime)
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

void BaseCamera::HandleLook(float deltaTime)
{
    if (!EngineContext->HasFocus())
        return;
    
    glm::vec2 mouseDelta = EngineContext->Input->GetDeltaMousePos();

    const float sens = 7.5f;
    transform.Rotate(glm::vec3(-mouseDelta.y, mouseDelta.x, 0) * sens * deltaTime);
}

void BaseCamera::Process(float deltaTime)
{
    HandleMovement(deltaTime);
    HandleLook(deltaTime);
}

bool BaseCamera::InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
        SetIsOrthographic(!orthographic);

    return false;
}
