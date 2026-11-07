#include "BaseCamera.h"

#include <algorithm>
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
    
    if (!orthographic)
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
        
    // return glm::ortho(-orthosize * aspectRatio, orthosize * aspectRatio, -orthosize, orthosize, nearPlane, farPlane);
       
    float left = -orthosize * aspectRatio;
    float right = orthosize * aspectRatio;
    float bottom = -orthosize;
    float top = orthosize;
    float near = nearPlane;
    float far = farPlane;
    
    
    float sx = 2.0f / (right - left);   // Converts the X axis to a range of 2
    float sy = 2.0f / (top - bottom);   // Converts the Y axis to a range of 2
    float sz = 2.0f / (far - near);     // Converts the Z axis to a range of 2
    
    float tx = - (right + left) / (right - left);    // Offsets the X axis to be between -1 and 1
    float ty = - (top + bottom) / (top - bottom);    // Offsets the Y axis to be between -1 and 1
    float tz = - (far + near)   / (far - near);      // Offsets the Z axis to be between -1 and 1
    
    // Transposed to match opengls ordering
    return glm::transpose(glm::mat4(
        sx,         0.0f,       0.0f,       tx,
        0.0f,       sy,         0.0f,       ty,
        0.0f,       0.0f,       -sz,        tz,
        0.0f,       0.0f,       0.0f,       1.0f
    ));
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
    
    float xRot = transform.GetRotation().x - mouseDelta.y * sens * deltaTime;
    xRot = std::clamp(xRot, -80.0f, 80.0f);
    float yRot = transform.GetRotation().y + mouseDelta.x * sens * deltaTime;
    
    transform.SetRotation({xRot, yRot, 0});
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
