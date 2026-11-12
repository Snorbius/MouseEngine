#pragma once
#include <map>

#include "Shader.h"

class Resource;
class Texture;
class BaseMesh;

class AssetManager
{
public:
    AssetManager() = default;
    ~AssetManager();
    
private:
    std::map<ShaderStruct, Shader*> loadedShaders;
    std::map<std::string, BaseMesh*> loadedMeshes;
    std::map<std::string, Texture*> loadedTextures;
    
    std::vector<Shader*> allShaders;
    
    std::map<std::string, Resource*> loadedResources;
    
public:
    /** Registers a loaded resource in the asset manager. Used internally by the engine, not meant to be called manually */
    void RegisterResource(const std::string& key, Resource* value) { loadedResources[key] = value; }

    /**
     * Fetches an already-loaded resource based on its file path. Use Resource::LoadResource to guarantee it gets loaded.
     * Returns null if the resource at that path has not been loaded yet.
     * @param filePath The path to the file.
     * @return The resource, or null if there is none.
     */
    Resource* FetchResource(const std::string& filePath);
    
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

    /**
     * Loads a texture from an image file.
     * @param texturePath The path to the texture file.
     * @param unique Whether it should load a unique copy.
     * @return The texture object.
     */
    Texture* LoadTexture(const std::string& texturePath, bool unique = false);

    /**
     * Get a map containing all loaded meshes.
     * @return The meshes.
     */
    std::map<std::string, BaseMesh*> GetAllLoadedMeshes() { return loadedMeshes; }

    /**
     * Get a list containing all loaded shaders.
     * @return The shaders.
     */
    std::vector<Shader*> GetAllLoadedShaders() { return allShaders; }
};