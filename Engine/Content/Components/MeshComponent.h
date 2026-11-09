#pragma once
#include "../../Renderable.h"
#include "../../Transform.h"
#include  "../../BaseMesh.h"

class MeshComponent: Renderable
{
public:
    MeshComponent();
    ~MeshComponent();
    
public:
    BaseMesh* mesh;
    Transform transform;
    
    void Render(Shader* shader) override;
};
