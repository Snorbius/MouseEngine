#include "Scene.h"
#include "../../Content/Components/MeshComponent.h"
#include "../ECS/ComponentManager.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Components/NameComponent.h"
#include "../ECS/Components/NewMeshComponent.h"
#include "../ECS/Components/TransformComponent.h"

Scene::Scene()
{
    MouseEngineContext* context = MouseEngineContext::GetInstance();
    context->Assets->LoadMesh("Engine/Content/Meshes/mouse.obj"); // Loads it to later re-use it for displaying the start positions
    context->Assets->LoadMesh("Engine/Content/Meshes/monkey.obj"); // Loads it to later re-use it for displaying the end positions
}

Scene::~Scene()
{
    for (MeshComponent*& meshComponent : sceneMeshes)
        delete meshComponent;
}

void Scene::LoadMeshes()
{
    if (!values.contains("mesh"))
        return;
    
    std::vector<std::string>& meshEntries = values["mesh"];
    for (const std::string& entry : meshEntries)
    {
        std::istringstream s(entry);
        std::string meshPath;
        std::string materialPath;
        glm::vec3 pos, rot, scale;
        
        TransformComponent transform;
        
        s >> meshPath
        >> pos.x >> pos.y >> pos.z
        >> rot.x >> rot.y >> rot.z
        >> scale.x >> scale.y >> scale.z
        >> materialPath;
        
        transform.SetPosition(pos);
        transform.SetRotation(rot);
        transform.SetScale(scale);
        
        BaseMesh* mesh = MouseEngineContext::GetInstance()->Assets->LoadMesh(meshPath);
        if (mesh == nullptr)
            continue;
        
        Material* material = LoadResource<Material>(materialPath);
        if (material == nullptr)
            material = Material::GetFallbackMaterial();
        
        NewMeshComponent meshComp(mesh, material);
        Entity entity = EngineContext->Entities->CreateEntity();
        EngineContext->Components->AddComponent(entity, transform);
        EngineContext->Components->AddComponent(entity, meshComp);
    }
}

void Scene::FetchStartLocations()
{
    if (!values.contains("start"))
        return;

    BaseMesh* mouseMesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/mouse.obj");
    NewMeshComponent mesh(mouseMesh, nullptr);
    
    for (const std::string& startLocation : values["start"])
    {
        std::istringstream s(startLocation);
        glm::vec3 location = glm::vec3(0.0f);
        s >> location.x >> location.y >> location.z;
        startLocations.push_back(location);
        
        Entity startEntity = EngineContext->Entities->CreateEntity();
        TransformComponent trans;
        trans.SetPosition(location);
        EngineContext->Components->AddComponent<TransformComponent>(startEntity, trans);
        EngineContext->Components->AddComponent<NewMeshComponent>(startEntity, mesh);
        EngineContext->Components->AddComponent<NameComponent>(startEntity).name = "Start Location";
    }
}

void Scene::FetchEndLocations()
{
    if (!values.contains("end"))
        return;

    BaseMesh* monkeyMesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/monkey.obj");
    NewMeshComponent mesh(monkeyMesh, nullptr);
    
    for (const std::string& endLocation : values["end"])
    {
        std::istringstream s(endLocation);
        glm::vec3 location = glm::vec3(0.0f);
        s >> location.x >> location.y >> location.z;
        endLocations.push_back(location);
        
        Entity endEntity = EngineContext->Entities->CreateEntity();
        EngineContext->Components->AddComponent<TransformComponent>(endEntity).SetPosition(location);
        EngineContext->Components->AddComponent<NewMeshComponent>(endEntity, mesh);
        EngineContext->Components->AddComponent<NameComponent>(endEntity).name = "End Location";
    }
}

void Scene::InitializeResource()
{
    if (values.contains("sceneName"))
        sceneName = values["sceneName"][0];
    
    LoadMeshes();
    FetchStartLocations();
    FetchEndLocations();
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

void Scene::Process(float deltaTime)
{
    
}
