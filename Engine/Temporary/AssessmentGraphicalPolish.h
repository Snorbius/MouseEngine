#pragma once
#include "../Object.h"
#include "../Content/Components/MeshComponent.h"

class Texture;

class AssessmentGraphicalPolish: Object, Renderable
{
public:
    AssessmentGraphicalPolish();
    
public:
    Texture* cirnoTexture;
    MeshComponent cirno;
    
    void Render(Shader* shader) override;
    void Process(float deltaTime) override;
};
