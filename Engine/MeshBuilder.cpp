#include "MeshBuilder.h"

#include <glm/geometric.hpp>

#include "LogManager.h"

void MeshBuilder::CalculateNormals()
{
    normals.clear();
    for (int i = 0; i < vertices.size(); ++i)
        normals.emplace_back(glm::vec3(0.0f));
    
    for (int i = 0; i < indices.size(); i++)
    {
        glm::vec3 v1 = vertices[indices[i].x];
        glm::vec3 v2 = vertices[indices[i].y];
        glm::vec3 v3 = vertices[indices[i].z];
        
        normals[indices[i].x] += (glm::normalize(glm::cross(v2 - v1, v3 - v1)));
        normals[indices[i].y] += (glm::normalize(glm::cross(v3 - v2, v1 - v2)));
        normals[indices[i].z] += (glm::normalize(glm::cross(v1 - v3, v2 - v3)));
    }

    for (glm::vec3& normal : normals)
        if (glm::length(normal) > 0.01f)
            normal = glm::normalize(normal);
}

BuiltMeshData MeshBuilder::BuildMesh()
{
    if (normals.empty())
        CalculateNormals();
    
    if (!normals.empty() && normals.size() != vertices.size())
        MouseLogs::print_warning("Number of normals does not match number of vertices.");
    
    if (!colors.empty() && colors.size() != vertices.size())
        MouseLogs::print_warning("Number of colors does not match number of vertices.");
    
    if (!uvs.empty() && uvs.size() != vertices.size())
        MouseLogs::print_warning("Number of uvs does not match number of vertices.");
    
    std::vector<float> vertexData;
    for (int i = 0; i < vertices.size(); ++i)
    {
        // TODO: Expand this with the rest of the data
        vertexData.emplace_back(vertices[i].x);
        vertexData.emplace_back(vertices[i].y);
        vertexData.emplace_back(vertices[i].z);
        
        glm::vec3 color = colors.size() > i ? colors[i] : defaultColor;
        vertexData.emplace_back(color.r);
        vertexData.emplace_back(color.g);
        vertexData.emplace_back(color.b);
        
        glm::vec2 uv = uvs.size() > i ? uvs[i] : glm::vec2(0.0f);
        vertexData.emplace_back(uv.x);
        vertexData.emplace_back(uv.y);
        
        glm::vec3 normal = normals.size() > i ? normals[i] : glm::vec3(0.0f);
        vertexData.emplace_back(normal.x);
        vertexData.emplace_back(normal.y);
        vertexData.emplace_back(normal.z);
    }
    
    std::vector<int> indexData;
    for (int i = 0; i < indices.size(); ++i)
    {
        indexData.emplace_back(indices[i].x);
        indexData.emplace_back(indices[i].y);
        indexData.emplace_back(indices[i].z);
    }
    
    return {
        .vertexData = vertexData,
        .indices = indexData
    };
}
