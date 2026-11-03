#include "PyramidMesh.h"

#include "../../MeshBuilder.h"

PyramidMesh::PyramidMesh()
{
    std::vector<glm::vec3> vertexData = {
        {-1, -1, -1},     // 0
        {1, -1, -1},      // 1
        {-1, -1, 1},      // 2
        {1, -1, 1},       // 3
        {0, 1, 0},        // 4
    };
    
    std::vector<glm::ivec3> indices = {
        {0, 2, 1},    // Bottom
        {2, 3, 1},    // Bottom
        {2, 0, 4},    // Left
        {1, 3, 4},    // Right
        {0, 1, 4},    // Back
        {3, 2, 4},    // Front
    };
    
    MeshBuilder builder;
    builder.vertices = vertexData;
    builder.indices = indices;
    
    BuiltMeshData data = builder.BuildMesh();
    
    useEbo = true;
    UpdateVertexData(data.vertexData, data.indices);
}
