#pragma once

#define USE_NAIVE_LOADER false
#include <string>

class BaseMesh;

class MeshLoader
{
private:
    static BaseMesh* LoadMeshNaiveLoader(const std::string& meshPath);
    static BaseMesh* LoadMeshExternalLoader(const std::string& meshPath);

public:
    /**
     * Creates a BaseMesh from a mesh file. Make sure this is what you want to use, consider taking a look at 
     * AssetManager::LoadMesh instead.
     * @param meshPath The path to the mesh file.
     * @return The newly created mesh.
     */
    static BaseMesh* LoadMesh(const std::string& meshPath);
};
