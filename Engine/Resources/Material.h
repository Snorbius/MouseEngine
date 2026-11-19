#pragma once
#include "Resource.h"

class Texture;
class Shader;




class Material: public Resource
{
private:
    static Material* fallbackMaterial;
    
public:
    Shader* shader;
    Texture* texture;
    
    std::string GetResourceIdentifier() override { return "Material"; }
    std::string GetResourceFileEnding() override { return "material"; }
    
    void InitializeResource() override;
    
    void Use();
    
    static Material* GetFallbackMaterial();
    static void CleanUp();
};
