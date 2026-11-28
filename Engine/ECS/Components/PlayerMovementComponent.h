#pragma once
#include "Component.h"
#include "../../Interfaces/ISerializable.h"

struct PlayerMovementComponent: Component, ISerializable
{
public:
    PlayerMovementComponent(float moveSpeed = 15.0f);
    
private:
    void HandleKeyboardMovement(float deltaTime);
    
public:
    float moveSpeed = 15.0f;
    Entity cameraPOV = 0;
    
    void Process(float deltaTime);
    std::string FetchSaveInfo() override;
};
