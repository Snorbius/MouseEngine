#pragma once
#include <string>

#include "Transform.h"

class Shader;

class Renderable
{
public:
    virtual ~Renderable() = default;
    virtual void Render(Shader* shader) = 0;
    
    static void RenderObject(std::string name, Transform transform, Shader* shader);
};
