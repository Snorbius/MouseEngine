#pragma once
#include "../Renderable.h"
#include "../Content/Meshes/CubeMesh.h"
#include "../Content/Meshes/SphereMesh.h"

class AssessmentDynamicScene: public Renderable
{
private:
    SphereMesh sphere;
    // CubeMesh cube;
    
public:
    void Render(Shader* shader) override;
};
