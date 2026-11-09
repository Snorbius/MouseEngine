#include "MeshComponent.h"

#include <glad/glad.h>

#include "../../BaseMesh.h"
#include "../../Shader.h"
#include "../../LogManager.h"

void MeshComponent::Render(Shader* shader)
{
    if (mesh == nullptr)
        return;
    
    shader->SetUniform("u_transform", transform.GetTransformMatrix());
    
    mesh->Render(shader);
    
    MouseLogs::glCheckError();
}
