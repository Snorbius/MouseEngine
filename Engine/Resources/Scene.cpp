#include "Scene.h"
#include "../../Content/Components/MeshComponent.h"
#include "../ECS/ComponentManager.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/CameraMovementComponent.h"
#include "../ECS/Components/NameComponent.h"
#include "../ECS/Components/NewMeshComponent.h"
#include "../ECS/Components/PlayerMovementComponent.h"
#include "../ECS/Components/TransformComponent.h"

Scene::~Scene()
{
    for (MeshComponent*& meshComponent : sceneMeshes)
        delete meshComponent;
}

std::vector<std::string> Scene::GetComponentParameters(std::string line)
{
    size_t startIndex = line.find('(') + 1;
    size_t endIndex = line.find(',', startIndex + 1);
    
    if (endIndex == std::string::npos)
        endIndex = line.find(')', startIndex + 1);
                
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
        
    std::fstream file(resourcePath);
            
    if (!file.is_open())
    {
        print_warning(std::format("Could not open file located at: {}", resourcePath));
        return;
    }
        
    std::string line;
    Entity currentEntity = 0;
    bool componentMode = false;
    
    ComponentManager* c = MouseEngineContext::GetInstance()->Components;
    
    while (std::getline(file, line))
    {
        if (line == "[Entity]")
        {
            currentEntity = MouseEngineContext::GetInstance()->Entities->CreateEntity();
            componentMode = true;
            continue;
        }
        
        if (line.empty() && componentMode)
        {
            componentMode = false;
            if (currentEntity != 0)
                sceneEntities.push_back(currentEntity);
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
            
            if (line.starts_with(Component::GetComponentName<NewMeshComponent>()))
            {
                std::vector<std::string> params = GetComponentParameters(line);
                c->AddComponent(currentEntity, NewMeshComponent(
                   MouseEngineContext::GetInstance()->Assets->LoadMesh(params[0]), 
                   LoadResource<Material>(params[1])
                ));
            }
            
            if (line.starts_with(Component::GetComponentName<NameComponent>()))
                c->AddComponent(currentEntity, NameComponent(GetComponentParameters(line)[0]));
            
            if (line.starts_with(Component::GetComponentName<PlayerMovementComponent>()))
                c->AddComponent(currentEntity, PlayerMovementComponent(std::stof(GetComponentParameters(line)[0])));
            
            if (line.starts_with(Component::GetComponentName<CameraMovementComponent>()))
                c->AddComponent<CameraMovementComponent>(currentEntity);
            
            if (line.starts_with(Component::GetComponentName<CameraComponent>()))
                c->AddComponent<CameraComponent>(currentEntity);
        }
    }
    
    file.close();
}

void Scene::InitializeResource()
{
    if (values.contains("sceneName"))
        sceneName = values["sceneName"][0];
    
    LoadEntities();
    
    values.clear();
}

void Scene::SaveToFile(std::string path)
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

    ComponentManager* c = MouseEngineContext::GetInstance()->Components;
    
    for (Entity entity : sceneEntities)
    {
        saveFile << "\n[Entity]\n";
        
        if (c->HasComponent<NameComponent>(entity)) 
            saveFile << GetSerializedData<NameComponent>(entity);
        
        if (c->HasComponent<TransformComponent>(entity)) 
            saveFile << GetSerializedData<TransformComponent>(entity);
        
        if (c->HasComponent<NewMeshComponent>(entity)) 
            saveFile << GetSerializedData<NewMeshComponent>(entity);
        
        if (c->HasComponent<CameraComponent>(entity)) 
            saveFile << GetSerializedData<CameraComponent>(entity);
        
        if (c->HasComponent<CameraMovementComponent>(entity)) 
            saveFile << GetSerializedData<CameraMovementComponent>(entity);
        
        if (c->HasComponent<PlayerMovementComponent>(entity)) 
            saveFile << GetSerializedData<PlayerMovementComponent>(entity);
    }
    
    saveFile.close();
}