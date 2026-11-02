#include "PyramidMesh.h"

PyramidMesh::PyramidMesh()
{
    float vertexData[] = {
        -1, -1, -1,     // 0
        1, -1, -1,      // 1
        -1, -1, 1,      // 2
        1, -1, 1,       // 3
        0, 1, 0,        // 4
    };
    
    int indices[] = {
        0, 1, 2,    // Bottom
        2, 1, 3,    // Bottom
        0, 4, 2,    // Left
        1, 3, 4,    // Right
        0, 1, 4,    // Back
        3, 4, 2,    // Front
    };
    
    useEbo = true;
    UpdateVertexData(vertexData, indices, sizeof(vertexData), sizeof(indices));
}
