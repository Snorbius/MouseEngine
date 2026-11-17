#pragma once
#include "../Object.h"
#include "../Content/Components/MeshComponent.h"

class Material;
class Texture;

class AssessmentGraphicalPolish: public Object
{
public:
    AssessmentGraphicalPolish();
    
public:
    MeshComponent shadedCirno;
    MeshComponent unlitCirno;
    MeshComponent monkey;
    MeshComponent icoSphere;
    MeshComponent mouse;
    MeshComponent hotdog;
    MeshComponent safi;
    
    void Process(float deltaTime) override;
};
