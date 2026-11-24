#pragma once
#include "Object.h"
#include "ECS/Components/Transform.h"

class Object3D: public Object
{
public:
    Object3D();
    
public:
    Transform transform;
};
