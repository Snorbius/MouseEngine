#include "MeshComponent.h"

#include "../../BaseMesh.h"
#include "../../BaseRenderer.h"
#include "../../Shader.h"
#include "../../Resources/Material.h"

MeshComponent::MeshComponent(): MeshComponent(nullptr, nullptr) { }

MeshComponent::MeshComponent(BaseMesh* aMesh, Material* aMaterial)
{
    mesh = aMesh;
    SetMaterial(aMaterial);
}

void MeshComponent::Render(Shader* shader)
{
    if (mesh == nullptr)
        return;
    
    shader->SetUniform("u_transform", transform.GetTransformMatrix());
    mesh->Render(shader);
}

void MeshComponent::SetMaterial(Material* newMaterial)
{
    material = newMaterial;
    MouseEngineContext::GetInstance()->Renderer->RegisterRenderable(this, material);
}
