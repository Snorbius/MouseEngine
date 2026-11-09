#include "MeshComponent.h"

#include <glad/glad.h>

#include "../../BaseMesh.h"
#include "../../Shader.h"
#include "../../LogManager.h"

MeshComponent::MeshComponent()
{
    mesh = new BaseMesh();
}

MeshComponent::~MeshComponent()
{
    delete mesh;
}

void MeshComponent::Render(Shader* shader)
{
    shader->SetUniform("u_transform", transform.GetTransformMatrix());
    
    mesh->Render(shader);
    
    MouseLogs::glCheckError();
}
