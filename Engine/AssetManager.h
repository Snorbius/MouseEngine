#pragma once
#include <map>

#include "Shader.h"

class AssetManager
{
public:
    AssetManager() = default;
    ~AssetManager();
    
private:
    std::map<ShaderStruct, Shader*> loadedShaders;
    
public:
    Shader* LoadShader(const ShaderStruct& shader, bool unique = false);
};
