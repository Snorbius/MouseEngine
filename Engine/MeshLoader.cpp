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
        
        // Fan triangulation, thanks Martin
        if (prefix == "f")
        {
            std::vector<std::string> faceTokens;
            std::string token;
            while (ss >> token)
                faceTokens.emplace_back(token);
            
            if (faceTokens.size() < 3)
                continue;

            for (int i = 1; i < faceTokens.size() - 1; ++i)
            {
                int triangleIndices[] = {0, i, i + 1};
                glm::ivec3 resultingIndices = glm::ivec3(0);

                for (int k = 0; k < 3; ++k)
                {
                    std::string kToken = faceTokens[triangleIndices[k]];
                    size_t firstSlash = kToken.find('/');
                    size_t secondSlash = kToken.find('/', firstSlash + 1);
                    
                    unsigned int posIndex = std::stoi(kToken.substr(0, firstSlash)) - 1;
                    unsigned int uvIndex = std::stoi(kToken.substr(firstSlash + 1, secondSlash - firstSlash - 1)) - 1;
                    unsigned int normalIndex = std::stoi(kToken.substr(secondSlash + 1)) - 1;
                    
                    glm::vec3 vPos = tempPos[posIndex];
                    glm::vec3 vNorm = tempNormals[normalIndex];
                    glm::vec2 vUv = tempUvs[uvIndex];
                    
                    int existingIndex = -1;

                    for (int i = 0; i < builder.vertices.size(); ++i)
                    {
                        if (builder.vertices[i] == vPos
                            && builder.normals[i] == vNorm
                            && builder.uvs[i] == vUv)
                        {
                            existingIndex = i;
                            break;
                        }
                    }
                    
                    if (existingIndex == -1)
                    {
                        resultingIndices[k] = builder.vertices.size();
                        
                        builder.vertices.emplace_back(vPos);
                        builder.normals.emplace_back(vNorm);
                        builder.uvs.emplace_back(vUv);
                    }
                    else
                    {
                        resultingIndices[k] = existingIndex;
                    }
                }
                
                builder.indices.emplace_back(resultingIndices);
            }
        }
    }
    
    file.close();
    
    BaseMesh* mesh = new BaseMesh();
    mesh->useEbo = true;
    mesh->UpdateVertexData(builder.BuildMesh());
    
    return mesh;
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
