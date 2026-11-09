#include "TriangleMesh.h"

#include "../../MeshBuilder.h"
#include "../../Shader.h"

TriangleMesh::TriangleMesh()
{
    std::vector<glm::vec3> vertexData = {
        {-1.0f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f},
    };
    
    std::vector<glm::ivec3> indices = {
        {0, 2, 1},
    };
    
    MeshBuilder builder;
    builder.vertices = vertexData;
    builder.indices = indices;
    
    BuiltMeshData data = builder.BuildMesh();
    
    mesh->useEbo = true;
    mesh->UpdateVertexData(data.vertexData, data.indices);
}