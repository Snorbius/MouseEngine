#pragma once
#include "../../Renderable.h"
#include "../../ECS/Components/Transform.h"
#include  "../../BaseMesh.h"

class Material;

class MeshComponent: public Renderable
{
public:
    MeshComponent();
    MeshComponent(BaseMesh* aMesh, Material* aMaterial);
    
private:
    Material* material = nullptr;
    
public:
    BaseMesh* mesh = nullptr;
    Transform transform;
    
    void Render(Shader* shader) override;
    Material* GetMaterial() const { return material; }
    void SetMaterial(Material* newMaterial);
};
