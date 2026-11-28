#pragma once
#include "Material.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Components/Component.h"

class MeshComponent;

class Scene: public Resource
{
public:
    Scene() = default;
    ~Scene() override;
    
private:
    std::vector<glm::vec3> endLocations;
    std::vector<MeshComponent*> endMeshes;
    
    std::vector<Entity> sceneEntities;
    
    std::vector<std::string> GetComponentParameters(std::string line);
    void LoadEntities();
    
    template<typename T>
    std::string GetSerializedData(Entity entity);
    
public:
    std::string sceneName = "placeholder";
    std::vector<MeshComponent*> sceneMeshes;
    std::vector<glm::vec3> startLocations;
    
    
    void InitializeResource() override;
    std::string GetResourceIdentifier() override { return "Scene"; }
    std::string GetResourceFileEnding() override { return "scene"; }
    void SaveToFile(std::string path) override;
};

template <typename T>
std::string Scene::GetSerializedData(Entity entity)
{
    T& comp = MouseEngineContext::GetInstance()->Components->GetComponent<T>(entity);
            
    std::string compName = Component::GetComponentName<T>();
    std::string data = comp.FetchSaveInfo();
    std::string fileData = std::format("{}({})", compName, data);
            
    return fileData + "\n";
}
