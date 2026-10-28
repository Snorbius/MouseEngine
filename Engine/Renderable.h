#pragma once

class Shader;

class Renderable
{
public:
    virtual ~Renderable() = default;
    virtual void Render(Shader* shader) = 0;
};
