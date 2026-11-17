#include "MeshComponent.h"

#include <glad/glad.h>

#include "../../BaseMesh.h"
#include "../../BaseRenderer.h"
#include "../../Shader.h"
#include "../../LogManager.h"
#include "../../Resources/Material.h"

MeshComponent::MeshComponent(): MeshComponent(nullptr, nullptr)
{
}

MeshComponent::MeshComponent(BaseMesh* aMesh, Material* aMaterial)
{
    mesh = aMesh;
    SetMaterial(aMaterial);
}

void MeshComponent::Render(Shader* shader)
{
    if (mesh == nullptr)
        return;
    
    if (shader == nullptr)
    {
        mesh->Render(nullptr);
        return;
    }
    
    if (material != nullptr && material->shader != nullptr)
    {
        shader->SetUniform("u_transform", transform.GetTransformMatrix());
        mesh->Render(shader);
        return;
    }
    
    shader->SetUniform("u_transform", transform.GetTransformMatrix());
    mesh->Render(shader);
    
    MouseLogs::glCheckError();
}

void MeshComponent::SetMaterial(Material* newMaterial)
{
    material = newMaterial;
    MouseEngineContext::GetInstance()->Renderer->RegisterRenderable(this, material);
}
