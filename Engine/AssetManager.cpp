#include "AssetManager.h"

#include "BaseMesh.h"
#include "MeshLoader.h"
#include "Texture.h"

AssetManager::~AssetManager()
{
    for (const std::pair<const ShaderStruct, Shader*>& shader : loadedShaders)
        if (shader.second != nullptr)
            delete shader.second;
    loadedShaders.clear();

    for (std::pair<const std::string, BaseMesh*>& mesh : loadedMeshes)
        if (mesh.second != nullptr)
            delete mesh.second;
    loadedMeshes.clear();

    for (std::pair<const std::string, Texture*>& texture : loadedTextures)
        if (texture.second != nullptr)
            delete texture.second;
    loadedTextures.clear();
}

Shader* AssetManager::LoadShader(const ShaderStruct& shader, bool unique)
{
    if (!unique && loadedShaders.contains(shader))
        return loadedShaders[shader];
    
    Shader* newShader = new Shader(shader);
    if (!unique)
        loadedShaders[shader] = newShader;
    
    allShaders.emplace_back(newShader);
    
    return newShader;
}

BaseMesh* AssetManager::LoadMesh(const std::string& meshPath, bool unique)
{
    if (!unique && loadedMeshes.contains(meshPath))
        return loadedMeshes[meshPath];
    
    BaseMesh* mesh = MeshLoader::LoadMesh(meshPath);
    if (!unique)
        loadedMeshes[meshPath] = mesh;
    
    return mesh;
}

Texture* AssetManager::LoadTexture(const std::string& texturePath, bool unique)
{
    if (!unique && loadedTextures.contains(texturePath))
        return loadedTextures[texturePath];
    
    Texture* texture = new Texture(texturePath);
    if (!unique)
        loadedTextures[texturePath] = texture;
    
    return texture;
}