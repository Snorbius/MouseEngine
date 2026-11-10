#include "Renderable.h"

#include <format>

#include "AssetManager.h"
#include "MouseEngineContext.h"

void Renderable::RenderObject(std::string name, Transform transform, Shader* shader)
{
    std::vector<BaseMesh*> meshes = MouseEngineContext::GetInstance()->Assets->GetAllLoadedMeshes();

    BaseMesh* mesh = nullptr;
    for (BaseMesh*& base_mesh : meshes)
    {
        if (base_mesh->meshName == name)
        {
            mesh = base_mesh;
            break;
        }
    }
    
    if (mesh == nullptr)
    {
        print_warning(std::format("Could not find mesh with name {}.", name));
        return;
    }
    
    shader->SetUniform("u_transform", transform.GetTransformMatrix());
    mesh->Render(shader);
}
