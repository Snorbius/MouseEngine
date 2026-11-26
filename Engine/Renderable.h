#pragma once
#include <string>

struct TransformComponent;
class Shader;

class Renderable
{
public:
    virtual ~Renderable();
    virtual void Render(Shader* shader) = 0;
    
    static void RenderObject(std::string name, TransformComponent transform, Shader* shader);
};
