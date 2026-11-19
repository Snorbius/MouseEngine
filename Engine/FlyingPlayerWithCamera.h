#pragma once
#include "FlyingPlayer.h"
#include "BaseCamera.h"
#include "CameraBoom.h"

class FlyingPlayerWithCamera: public FlyingPlayer
{
public:
    FlyingPlayerWithCamera();
    
private:
    const float minBoomRange = 3.0f;
    const float maxBoomRange = 30.0f;
    BaseCamera camera;
    CameraBoom boom;
    
    void HandleLook(float deltaTime);
    void HandleZoom();
    
public:
    void Process(float deltaTime) override;
};
