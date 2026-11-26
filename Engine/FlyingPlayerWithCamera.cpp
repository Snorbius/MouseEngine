#include "FlyingPlayerWithCamera.h"

#include <algorithm>

#include "InputManager.h"
#include "MouseEngineContext.h"

FlyingPlayerWithCamera::FlyingPlayerWithCamera()
{
    playerCamera = &camera;
    
    boom.target = this;
    boom.camera = &camera;
}

void FlyingPlayerWithCamera::Process(float deltaTime)
{
    FlyingPlayer::Process(deltaTime); // movement
    
    HandleLook(deltaTime);
    HandleZoom();
}

void FlyingPlayerWithCamera::HandleLook(float deltaTime)
{
    if (!EngineContext->HasFocus()
        || !(EngineContext->Input->GetMouseCaptured() && !EngineContext->Input->GetMouseVisible()))
        return;
    
    glm::vec2 input = glm::vec2(0);
    
    if (inputMode == WASD || inputMode == ARROWS)
        input = EngineContext->Input->GetDeltaMousePos();
    else if (inputMode == CONTROLLER1)
        input = EngineContext->Input->GetControllerAxisValue(0, 1);
    else if (inputMode == CONTROLLER2)
        input = EngineContext->Input->GetControllerAxisValue(1, 1);

    TransformComponent& targetTransform = boom.transform;
    
    const float sens = (inputMode == WASD || inputMode == ARROWS) ? 7.5f : 75.0f;
    
    float xRot = targetTransform.GetRotation().x - input.y * sens * deltaTime;
    xRot = std::clamp(xRot, -80.0f, 80.0f);
    float yRot = targetTransform.GetRotation().y + input.x * sens * deltaTime;
    
    targetTransform.SetRotation({xRot, yRot, 0});
}

void FlyingPlayerWithCamera::HandleZoom()
{
    
}
