#include "CubeMesh.h"

CubeMesh::CubeMesh()
{
    float vertexData[] = {
        -1, -1, -1, // 0
        -1, 1, -1,  // 1
        1, -1, -1,  // 2
        1, 1, -1,   // 3
        -1, -1, 1,  // 4
        -1, 1, 1,   // 5
        1, -1, 1,   // 6
        1, 1, 1,    // 7
    };
    
    int indices[] = {
        0, 2, 1,    // Back
        1, 2, 3,    // Back
        4, 5, 6,    // Front
        5, 7, 6,    // Front
        2, 3, 6,    // Right
        3, 6, 7,    // Right
        0, 1, 4,    // Left
        1, 5, 4,    // Left
        1, 5, 3,    // Top
        5, 7, 3,    // Top
        0, 2, 4,    // Bottom
        4, 2, 6,    // Bottom
    };
    
    useEbo = true;
    UpdateVertexData(vertexData, indices, sizeof(vertexData), sizeof(indices));
}
