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
    /**
     * Loads a shader based on the shader parameter. The 'unique' parameter determines if it should load a unique copy
     * of the shader. Use this whenever you want to make changes that should not be applied to every other copy of the
     * same shader, for example when using uniforms.
     * @param shader The data from which to load the shader.
     * @param unique Whether it should load a unique copy of the shader.
     * @return The newly created shader.
     */
    Shader* LoadShader(const ShaderStruct& shader, bool unique = false);
};
