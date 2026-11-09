#include "MeshLoader.h"

#include <format>
#include <sstream>
#include <OBJ_Loader/OBJ_Loader.h>

#include "BaseMesh.h"
#include "LogManager.h"
#include "MeshBuilder.h"

BaseMesh* MeshLoader::LoadMeshNaiveLoader(const std::string& meshPath)
{
    // Thank you, Martin, for showing the highly convenient extraction operator
    
    std::ifstream file(meshPath);
    if (!file.is_open())
    {
        MouseLogs::print_warning(std::format("Could not load mesh located at {}.", meshPath));
        return nullptr;
    }
    
    MeshBuilder builder;
    
    std::vector<glm::vec3> tempPos;
    std::vector<glm::vec3> tempNormals;
    std::vector<glm::vec2> tempUvs;
    
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;
        
        if (prefix == "v")
        {
            glm::vec3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            tempPos.emplace_back(pos);
        }
        else if (prefix == "vn")
        {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            tempNormals.emplace_back(normal);
        }
        else if (prefix == "vt")
        {
            glm::vec2 uv;
            ss >> uv.x >> uv.y;
            tempUvs.emplace_back(uv);
        }
    }
    
    return nullptr;
}

BaseMesh* MeshLoader::LoadMeshExternalLoader(const std::string& meshPath)
{
    objl::Loader loader;
    
    loader.LoadFile(meshPath);
    
    MeshBuilder builder;
    for (objl::Vertex vertex : loader.LoadedVertices)
    {
        objl::Vector3 pos = vertex.Position;
        objl::Vector3 normal = vertex.Normal;
        objl::Vector2 uv = vertex.TextureCoordinate;
        
        builder.vertices.emplace_back(pos.X, pos.Y, pos.Z);
        builder.normals.emplace_back(normal.X, normal.Y, normal.Z);
        builder.uvs.emplace_back(uv.X, uv.Y);
    }

    for (int i = 0; i < loader.LoadedIndices.size(); i += 3)
        builder.indices.emplace_back(loader.LoadedIndices[i + 0], loader.LoadedIndices[i + 1], loader.LoadedIndices[i + 2]);
    
    BaseMesh* mesh = new BaseMesh();
    mesh->useEbo = true;
    
    BuiltMeshData data = builder.BuildMesh();
    mesh->UpdateVertexData(data.vertexData, data.indices);
    
    return mesh;
}

BaseMesh* MeshLoader::LoadMesh(const std::string& meshPath)
{
#if USE_NAIVE_LOADER
    return LoadMeshNaiveLoader(meshPath);
#endif
    
    return LoadMeshExternalLoader(meshPath);
}
