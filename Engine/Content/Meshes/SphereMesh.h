#pragma once
#include "../../BaseMesh.h"
#include "../../Object.h"

class SphereMesh: public BaseMesh, Object
{
public:
    SphereMesh();
    
    void Process(float deltaTime) override;
};
