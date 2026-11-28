#pragma once
#include "Component.h"
#include "../../Interfaces/ISerializable.h"

struct CameraMovementComponent: Component, ISerializable
{
public:
    void Process(float deltaTime);
    std::string FetchSaveInfo() override;
};
