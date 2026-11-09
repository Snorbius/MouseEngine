#pragma once
#include "../Renderable.h"
#include "../Content/Meshes/CubeMesh.h"
#include "../Content/Meshes/PyramidMesh.h"
#include "../Content/Meshes/SphereMesh.h"
#include "../Object.h"

class Assessment3D: public Object, Renderable
{
public:
    Assessment3D();
    
private:
    CubeMesh cube;
    PyramidMesh pyramid;
    SphereMesh sphere;
    
public:
    void Render(Shader* shader) override;
    void Process(float deltaTime) override;
};
