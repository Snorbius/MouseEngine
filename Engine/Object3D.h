#pragma once
#include "Object.h"
#include "Transform.h"

class Object3D: public Object
{
public:
    Transform transform;
};
