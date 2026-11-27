#pragma once
#include "Component.h"

struct PlayerMovementComponent: Component
{
private:
    void HandleKeyboardMovement(float deltaTime);
    
public:
    float moveSpeed = 15.0f;
    Entity cameraPOV;
    
    void Process(float deltaTime);
};
