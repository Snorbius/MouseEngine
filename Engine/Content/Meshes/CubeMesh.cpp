#include "CubeMesh.h"

#include "../../MeshBuilder.h"

CubeMesh::CubeMesh()
{
    std::vector<glm::vec3> vertices = {
        {-1, -1, 1},    // 0
        {-1, 1, 1},     // 1
        {1, -1, 1},     // 2
        {1, 1, 1},      // 3
        {-1, -1, -1},   // 4
        {-1, 1, -1},    // 5
        {1, -1, -1},    // 6
        {1, 1, -1},     // 7
    };
    
    std::vector<glm::vec3> color = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0},
        {0, 1, 0},
    };
    
    std::vector<glm::ivec3> indices = {
        {0, 2, 1},    // Back
        {1, 2, 3},    // Back
        {4, 5, 6},    // Front
        {5, 7, 6},    // Front
        {2, 6, 3},    // Right
        {3, 6, 7},    // Right
        {0, 1, 4},    // Left
        {1, 5, 4},    // Left
        {1, 3, 5},    // Top
        {5, 3, 7},    // Top
        {0, 4, 2},    // Bottom
        {4, 6, 2},    // Bottom
    };
    
    std::vector<glm::vec2> uvs = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1},
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1},
    };
    
    
    MeshBuilder builder;
    builder.vertices = vertices;
    builder.indices = indices;
    builder.colors = color;
    builder.uvs = uvs;
    
    useEbo = true;
    BuiltMeshData data = builder.BuildMesh();
    UpdateVertexData(data.vertexData, data.indices);
}
