#pragma once
#include "Resource.h"

class Texture;
class Shader;

class Material: public Resource
{
protected:
    
public:
    Shader* shader;
    Texture* texture;
    
    std::string GetResourceIdentifier() override { return "Material"; }
    
    void InitializeResource() override;
    
    void Use();
};
