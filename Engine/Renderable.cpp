#include "Renderable.h"

#include <format>

#include "AssetManager.h"
#include "MouseEngineContext.h"

void Renderable::RenderObject(std::string name, Transform transform, Shader* shader)
{
    std::map<std::string, BaseMesh*> meshes = MouseEngineContext::GetInstance()->Assets->GetAllLoadedMeshes();

    BaseMesh* mesh = nullptr;
    for (std::pair<const std::string, BaseMesh*>& pair : meshes)
    {
        if (pair.second->meshName == name)
        {
            mesh = pair.second;
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
