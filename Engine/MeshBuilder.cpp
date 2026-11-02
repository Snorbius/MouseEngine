#include "MeshBuilder.h"

#include "LogManager.h"

BuiltMeshData MeshBuilder::BuildMesh()
{
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
