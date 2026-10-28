#include "TriangleMesh.h"

#include <glad/glad.h>

#include "../../Shader.h"

TriangleMesh::TriangleMesh()
{
    float vertexData[] = {
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
    };
    
    UpdateVertexData(vertexData, sizeof(vertexData));
}