#pragma once
#include <map>

#include "Shader.h"

class BaseMesh;

class AssetManager
{
public:
    AssetManager() = default;
    ~AssetManager();
    
private:
    std::map<ShaderStruct, Shader*> loadedShaders;
    std::map<std::string, BaseMesh*> loadedMeshes;
    
public:
    /**
     * Loads a shader based on the shader parameter. The 'unique' parameter determines if it should load a unique copy
     * of the shader. Use this whenever you want to make changes that should not be applied to every other copy of the
     * same shader, for example when using uniforms.
     * @param shader The data from which to load the shader.
     * @param unique Whether it should load a unique copy.
     * @return The shader object.
     */
    Shader* LoadShader(const ShaderStruct& shader, bool unique = false);

    /**
     * Loads a mesh from a mesh file. The 'unique' parameter can be used if you plan to alter the mesh data 
     * during run-time.
     * @param meshPath The path to the mesh file.
     * @param unique Whether it should load a unique copy.
     * @return The mesh object.
     */
    BaseMesh* LoadMesh(const std::string& meshPath, bool unique = false);
};
