#pragma once
#include "Object3D.h"
#include "Content/Components/MeshComponent.h"

class BaseCamera;

enum PlayerInputMode
{
    WASD,
    ARROWS,
    CONTROLLER1,
    CONTROLLER2,
};

class FlyingPlayer: public Object3D
{
public:
    FlyingPlayer();
    
private:
    MeshComponent playerMesh;
    
    void HandleMovement(float deltaTime);
    
protected:
    PlayerInputMode inputMode = WASD;

public:
    BaseCamera* playerCamera = nullptr;
    
    void Process(float deltaTime) override;
    void SetInputMode(PlayerInputMode mode);
};
