#pragma once
#include "Object.h"
#include "ECS/Components/TransformComponent.h"

class Object3D: public Object
{
public:
    TransformComponent transform;
};
