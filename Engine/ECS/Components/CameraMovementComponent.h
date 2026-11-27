#pragma once
#include "Component.h"

struct CameraMovementComponent: Component
{
public:
    void Process(float deltaTime);
};
