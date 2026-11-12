#pragma once
#include "../../Renderable.h"
#include "../../Transform.h"
#include  "../../BaseMesh.h"

class Material;

class MeshComponent: Renderable
{
public:
    BaseMesh* mesh;
    Transform transform;
    Material* material;
    
    void Render(Shader* shader) override;
};
