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
    
    glm::vec2 mouseDelta = EngineContext->Input->GetDeltaMousePos();

    Transform* targetTransform = &boom.transform;
    
    const float sens = 7.5f;
    
    float xRot = targetTransform->GetRotation().x - mouseDelta.y * sens * deltaTime;
    xRot = std::clamp(xRot, -80.0f, 80.0f);
    float yRot = targetTransform->GetRotation().y + mouseDelta.x * sens * deltaTime;
    
    targetTransform->SetRotation({xRot, yRot, 0});
}

void FlyingPlayerWithCamera::HandleZoom()
{
    
}
