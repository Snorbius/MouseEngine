#pragma once
#include "../Object.h"
#include "../Content/Components/MeshComponent.h"

class Material;
class Texture;

class AssessmentGraphicalPolish: Object, Renderable
{
private:
    Material* cirnoMaterial;
    
public:
    AssessmentGraphicalPolish();
    
public:
    MeshComponent cirno;
    
    void Render(Shader* shader) override;
    void Process(float deltaTime) override;
};
