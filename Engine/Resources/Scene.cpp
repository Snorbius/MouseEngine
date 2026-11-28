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
        
        sceneEntities.push_back(entity);
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

std::vector<std::string> Scene::GetComponentParameters(std::string line)
{
    size_t startIndex = line.find('(') + 1;
    size_t endIndex = line.find(',', startIndex + 1);
                
    std::vector<std::string> params;
                
    while (endIndex != std::string::npos)
    {
        std::string result = line.substr(startIndex, endIndex - startIndex);
        startIndex = endIndex + 1;
        endIndex = line.find(',', startIndex + 1);
        if (endIndex == std::string::npos)
            endIndex = line.find(')', startIndex + 1);
                    
        if (result.empty())
            continue;
                    
        result = result.substr(result.find_first_not_of(' '));
                    
        params.push_back(result);
    }
    return params;
}

void Scene::LoadEntities()
{
    if (!std::filesystem::exists(resourcePath))
    {
        print_line(std::format("Could not find specified file: {}", resourcePath));
        return;
    }
        
    std::fstream file("Engine/Content/Scenes/Temporary.scene");
            
    if (!file.is_open())
    {
        print_warning(std::format("Could not open file located at: {}", resourcePath));
        return;
    }
        
    std::string line;
    Entity currentEntity = 0;
    bool componentMode = false;
    
    ComponentManager* c = EngineContext->Components;
    
    while (std::getline(file, line))
    {
        if (line == "[Entity]")
        {
            currentEntity = EngineContext->Entities->CreateEntity();
            componentMode = true;
            continue;
        }
        
        if (line.empty())
        {
            componentMode = false;
            // if (currentEntity != 0)
            //     sceneEntities.push_back(currentEntity);
            continue;
        }
        
        if (componentMode)
        {
            if (line.starts_with(Component::GetComponentName<TransformComponent>()))
            {
                std::vector<std::string> params = GetComponentParameters(line);
                
                glm::vec3 pos, rot, scale;
                pos.x = std::stof(params[0]);
                pos.y = std::stof(params[1]);
                pos.z = std::stof(params[2]);
                rot.x = std::stof(params[3]);
                rot.y = std::stof(params[4]);
                rot.z = std::stof(params[5]);
                scale.x = std::stof(params[6]);
                scale.y = std::stof(params[7]);
                scale.z = std::stof(params[8]);
                
                TransformComponent transform(pos, rot, scale);
                c->AddComponent(currentEntity, transform);
            }
        }
    }
    
    file.close();
}

void Scene::InitializeResource()
{
    if (values.contains("sceneName"))
        sceneName = values["sceneName"][0];
    
    LoadMeshes();
    FetchStartLocations();
    FetchEndLocations();
    
    LoadEntities();
    
    NewSaveToFile("Engine/Content/Scenes/Temporary.scene");
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

void Scene::NewSaveToFile(std::string path)
{
    std::string fileEnding = GetResourceFileEnding();
    if (!path.ends_with("." + fileEnding))
        path += "." + fileEnding;

    std::ofstream saveFile(path);
    
    if (!saveFile.is_open())
    {
        print_warning(std::format("Could not create file at \"{}\", could not open file.", path));
        saveFile.close();
        return;
    }
    
    saveFile << GetResourceIdentifier() << "\n";

    ComponentManager* c = EngineContext->Components;
    
    for (Entity entity : sceneEntities)
    {
        saveFile << "\n[Entity]\n";
        
        if (c->HasComponent<TransformComponent>(entity))
        {
            TransformComponent& trans = c->GetComponent<TransformComponent>(entity);
            std::string typeName = typeid(TransformComponent).name();
            
            std::string compName = typeName.substr(typeName.find(' ') + 1);
            std::string data = trans.FetchSaveInfo();
            std::string fileData = std::format("{}({})", compName, data);
            
            saveFile << fileData + "\n";
            
            print_debug_line("Test");
        }
    }
    
    saveFile.close();
}

void Scene::Process(float deltaTime)
{
    
}
