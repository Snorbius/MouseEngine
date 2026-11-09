#include "AssetManager.h"

AssetManager::~AssetManager()
{
    for (const std::pair<const ShaderStruct, Shader*>& shader : loadedShaders)
        if (shader.second != nullptr)
            delete shader.second;
    
    loadedShaders.clear();
}

Shader* AssetManager::LoadShader(const ShaderStruct& shader, bool unique)
{
    if (!unique && loadedShaders.contains(shader))
        return loadedShaders[shader];
    
    Shader* newShader = new Shader(shader);
    if (!unique)
        loadedShaders[shader] = newShader;
    
    return newShader;
}
