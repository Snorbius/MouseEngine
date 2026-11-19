#pragma once
#include "Object3D.h"

class BaseCamera;

class CameraBoom: public Object3D
{
public:
    CameraBoom();
    
public:
    Object3D* target;
    BaseCamera* camera;
    glm::vec3 offset = glm::vec3(0, 3, 0);
    float targetRange = 15;
    
    void Process(float deltaTime) override;
};
