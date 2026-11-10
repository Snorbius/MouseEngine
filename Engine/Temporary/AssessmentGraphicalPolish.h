#pragma once
#include "../Object.h"
#include "../Content/Components/MeshComponent.h"

class AssessmentGraphicalPolish: Object, Renderable
{
public:
    AssessmentGraphicalPolish();
    
public:
    MeshComponent cirno;
    
    void Render(Shader* shader) override;
    void Process(float deltaTime) override;
};
