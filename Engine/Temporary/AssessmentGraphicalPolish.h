#pragma once
#include "../Object.h"
#include "../Content/Components/MeshComponent.h"

class Material;
class Texture;

class AssessmentGraphicalPolish: Object, Renderable
{
private:
    Material* shadedCirnoMaterial;
    Material* unlitCirnoMaterial;
    
public:
    AssessmentGraphicalPolish();
    
public:
    MeshComponent shadedCirno;
    MeshComponent unlitCirno;
    
    void Render(Shader* shader) override;
    void Process(float deltaTime) override;
};
