#include "CameraMovementComponent.h"

#include <algorithm>

#include "TransformComponent.h"
#include "../../InputManager.h"

void CameraMovementComponent::Process(float deltaTime)
{
    if (!EngineContext->HasFocus()
        || !(EngineContext->Input->GetMouseCaptured() && !EngineContext->Input->GetMouseVisible()))
        return;
    
    glm::vec2 input = EngineContext->Input->GetDeltaMousePos();

    
    TransformComponent& targetTransform = EngineContext->Components->GetComponent<TransformComponent>(owningEntity);

    constexpr float sens = 7.5f;
    
    float xRot = targetTransform.GetRotation().x - input.y * sens * deltaTime;
    xRot = std::clamp(xRot, -80.0f, 80.0f);
    float yRot = targetTransform.GetRotation().y + input.x * sens * deltaTime;
    
    targetTransform.SetRotation({xRot, yRot, 0});
}
