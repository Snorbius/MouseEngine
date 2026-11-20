#include "Scene.h"

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

void Scene::FetchStartLocations()
{
    if (!values.contains("start"))
        return;

    BaseMesh* mouseMesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/mouse.obj");
    
    for (const std::string& startLocation : values["start"])
    {
        std::istringstream s(startLocation);
        glm::vec3 location = glm::vec3(0.0f);
        s >> location.x >> location.y >> location.z;
        startLocations.push_back(location);
        
        MeshComponent* startMesh = new MeshComponent(mouseMesh, nullptr);
        startMesh->transform.SetPosition(location);
        sceneMeshes.push_back(startMesh);
    }
    
    if (startLocations.empty())
        startLocations.emplace_back(0);
}

void Scene::FetchEndLocations()
{
    if (!values.contains("end"))
        return;

    BaseMesh* monkeyMesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/monkey.obj");
    
    for (const std::string& endLocation : values["end"])
    {
        std::istringstream s(endLocation);
        glm::vec3 location = glm::vec3(0.0f);
        s >> location.x >> location.y >> location.z;
        endLocations.push_back(location);
        
        MeshComponent* endMesh = new MeshComponent(monkeyMesh, nullptr);
        endMesh->transform.SetPosition(location);
        sceneMeshes.push_back(endMesh);
        endMeshes.push_back(endMesh);
    }
    
    if (endLocations.empty())
        endLocations.emplace_back(0, 0, 5);
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
