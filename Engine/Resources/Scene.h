#pragma once
#include "Material.h"

class Scene: public Resource
{
public:
    Scene() = default;
    ~Scene();
    
private:
    void LoadMeshes();
    
public:
    std::string sceneName = "placeholder";
    std::vector<MeshComponent*> sceneMeshes;
    
    void InitializeResource() override;
    std::string GetResourceIdentifier() override { return "Scene"; }
    std::string GetResourceFileEnding() override { return "scene"; }
    void SaveToFile(std::string path) override;
};
