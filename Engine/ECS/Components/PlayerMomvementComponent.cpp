#include "PlayerMovementComponent.h"

#include "../../InputManager.h"
#include <glm/vec3.hpp>

#include "TransformComponent.h"

void PlayerMovementComponent::HandleKeyboardMovement(float deltaTime)
{
    std::optional<TransformComponent> trans = TryGetSiblingComponent<TransformComponent>();
    if (!trans.has_value())
        return;
    
    // TransformComponent& transform = trans.value();
    TransformComponent& transform = EngineContext->Components->GetComponent<TransformComponent>(owningEntity);
    
    constexpr int forwardKey = GLFW_KEY_W;
    constexpr int backwardKey = GLFW_KEY_S;
    constexpr int rightKey = GLFW_KEY_D;
    constexpr int leftKey = GLFW_KEY_A;
    constexpr int upKey = GLFW_KEY_SPACE;
    constexpr int downKey = GLFW_KEY_LEFT_CONTROL;
 
    glm::vec3 move = glm::vec3(0.0f);
    
    if (EngineContext->Input->IsKeyHeld(forwardKey))
        move.z += 1.0f;
    if (EngineContext->Input->IsKeyHeld(backwardKey))
        move.z -= 1.0f;
    if (EngineContext->Input->IsKeyHeld(rightKey))
        move.x += 1.0f;
    if (EngineContext->Input->IsKeyHeld(leftKey))
        move.x -= 1.0f;
    if (EngineContext->Input->IsKeyHeld(upKey))
        move.y += 1.0f;
    if (EngineContext->Input->IsKeyHeld(downKey))
        move.y -= 1.0f;
    
    if (glm::length(move) < 0.01)
        return;
    
    glm::vec3 moveVector = glm::vec3(0.0f);
    
    std::optional<TransformComponent> cameraTrans = EngineContext->Components->TryGetComponent<TransformComponent>(cameraPOV);
    TransformComponent axis = cameraTrans.has_value() ? cameraTrans.value() : TransformComponent();
    
    moveVector += move.x * axis.GetRight();
    moveVector += move.y * axis.GetUp();
    moveVector += move.z * axis.GetForward();

    moveVector = glm::normalize(moveVector);

    transform.Translate(moveVector * moveSpeed * deltaTime);
}

void PlayerMovementComponent::Process(float deltaTime)
{
    HandleKeyboardMovement(deltaTime);
}
