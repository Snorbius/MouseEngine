#include "MeshComponent.h"

#include <glad/glad.h>

#include "../../BaseMesh.h"
#include "../../Shader.h"
#include "../../LogManager.h"
#include "../../Resources/Material.h"

void MeshComponent::Render(Shader* shader)
{
    if (mesh == nullptr)
        return;
    
    if (material != nullptr && material->shader != nullptr)
    {
        material->Use();
        material->shader->SetUniform("u_transform", transform.GetTransformMatrix());
        mesh->Render(material->shader);
        return;
    }
    
    shader->SetUniform("u_transform", transform.GetTransformMatrix());
    
    mesh->Render(shader);
    
    MouseLogs::glCheckError();
}
