#pragma once
#include "../../Renderable.h"
#include  "../../BaseMesh.h"
#include "../ECS/Components/TransformComponent.h"

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
    TransformComponent transform;
    
    void Render(Shader* shader) override;
    Material* GetMaterial() const { return material; }
    void SetMaterial(Material* newMaterial);
};
