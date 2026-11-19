#include "Scene.h"

void Scene::LoadMeshes()
{
    if (!values.contains("mesh"))
        return;
    
    std::vector<std::string>& meshEntries = values["mesh"];
    for (const std::string& entry : meshEntries)
    {
        std::istringstream s(entry);
        std::string meshPath;
        std::string materialPath = "";
        glm::vec3 pos, rot, scale;
        
        s >> meshPath
        >> pos.x >> pos.y >> pos.z
        >> rot.x >> rot.y >> rot.z
        >> scale.x >> scale.y >> scale.z
        >> materialPath;
        
        BaseMesh* mesh = MouseEngineContext::GetInstance()->Assets->LoadMesh(meshPath);
        if (mesh == nullptr)
            continue;
        
        Material* meshMaterial = materialPath.empty() ? nullptr : LoadResource<Material>(materialPath);
        
        MeshComponent* newMesh = new MeshComponent(mesh, meshMaterial);
        sceneMeshes.push_back(newMesh);
        
        newMesh->transform.SetPosition(pos);
        newMesh->transform.SetRotation(rot);
        newMesh->transform.SetScale(scale);
    }
}

void Scene::InitializeResource()
{
    if (values.contains("sceneName"))
        sceneName = values["sceneName"][0];
    
    LoadMeshes();
}

void Scene::SaveToFile(std::string path)
{
    values.clear();
    
    AddValue("sceneName", sceneName);

    for (MeshComponent*& mesh : sceneMeshes)
    {
        glm::vec3 pos = mesh->transform.GetPosition();
        glm::vec3 rot = mesh->transform.GetRotation();
        glm::vec3 scale = mesh->transform.GetScale();
        
        std::string value = std::format(
        "{} "
        "{} {} {} "
        "{} {} {} "
        "{} {} {} "
        "{}",
        mesh->mesh->meshPath,
        pos.x, pos.y, pos.z,
        rot.x, rot.y, rot.z,
        scale.x, scale.y, scale.z,
        mesh->GetMaterial()->resourcePath
        );
        
        AddValue("mesh", value);
    }
    
    Resource::SaveToFile(path);
    
    values.clear();
}
