#pragma once
#include "Resource.h"

class Texture;
class Shader;

class Material: public Resource
{
protected:
    std::string GetResourceIdentifier() override { return "Material"; }
    
public:
    Shader* shader;
    Texture* texture;
    
    void InitializeResource() override;
    
    void Use();
};
