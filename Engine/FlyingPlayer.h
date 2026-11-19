#pragma once
#include "Object3D.h"
#include "Content/Components/MeshComponent.h"

class BaseCamera;

enum PlayerInputMode
{
    WASD,
    ARROWS,
};

class FlyingPlayer: public Object3D
{
public:
    FlyingPlayer();
    
private:
    MeshComponent playerMesh;
    PlayerInputMode inputMode = WASD;
    
    void HandleMovement(float deltaTime);
    
public:
    BaseCamera* playerCamera = nullptr;
    
    void Process(float deltaTime) override;
    void SetInputMode(PlayerInputMode mode);
};
