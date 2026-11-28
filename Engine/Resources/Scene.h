#pragma once
#include "Material.h"
#include "../Object.h"
#include "../ECS/EntityManager.h"

class MeshComponent;

class Scene: public Resource, Object
{
public:
    Scene();
    ~Scene() override;
    
private:
    std::vector<glm::vec3> endLocations;
    std::vector<MeshComponent*> endMeshes;
    
    std::vector<Entity> sceneEntities;
    
    void LoadMeshes();
    void FetchStartLocations();
    void FetchEndLocations();
    std::vector<std::string> GetComponentParameters(std::string line);
    void LoadEntities();
    
public:
    std::string sceneName = "placeholder";
    std::vector<MeshComponent*> sceneMeshes;
    std::vector<glm::vec3> startLocations;
    
    
    void InitializeResource() override;
    std::string GetResourceIdentifier() override { return "Scene"; }
    std::string GetResourceFileEnding() override { return "scene"; }
    void SaveToFile(std::string path) override;
    void NewSaveToFile(std::string path);
    
    void Process(float deltaTime) override;
};
