#include "BaseMesh.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "LogManager.h"
#include "Shader.h"

void BaseMesh::UpdateVertexData(const float* data, int size)
{
    if (useEbo)
        MouseLogs::print_debug_line("You appear to have used a non-ebo mesh function for a mesh with ebo enabled.\n"
                                    "Are you sure this is what you want?");
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    
    int numFloats = static_cast<int>(size / sizeof(float));
    if (numFloats % floatsPerVertex != 0)
        MouseLogs::print_warning("Size of data does not match attribute configuration");
    vertexCount = numFloats / floatsPerVertex;
}

void BaseMesh::UpdateVertexData(const std::vector<float>& data)
{
    UpdateVertexData(data.data(), static_cast<int>(data.size() * sizeof(float)));
}

void BaseMesh::UpdateVertexData(const float* vertexData, const int* indices, int dataSize, int indicesSize)
{
    if (!useEbo)
        MouseLogs::print_debug_line("You appear to have used an ebo function without enabled useEbo.\n"
                                    "Are you sure this is what you want?");

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, dataSize, vertexData, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    
    vertexCount = static_cast<int>(floor(indicesSize / sizeof(int)));
}

void BaseMesh::UpdateVertexData(const std::vector<float>& vertexData, const std::vector<int>& indices)
{
    UpdateVertexData(vertexData.data(), indices.data(), 
        static_cast<int>(vertexData.size() * sizeof(float)), 
        static_cast<int>(indices.size() * sizeof(int)));
}

BaseMesh::BaseMesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    
    float stride = sizeof(float) * 8;
    
    // Location
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Uv
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

BaseMesh::~BaseMesh()
{
    if (vao)
        glDeleteVertexArrays(1, &vao);
    if (vbo)
        glDeleteBuffers(1, &vbo);
    if (ebo)
        glDeleteBuffers(1, &ebo);
}

void BaseMesh::Render(Shader* shader)
{
    shader->SetUniform("u_transform", transform.GetTransformMatrix());
    
    shader->Use();
    glBindVertexArray(vao);
    
    if (useEbo)
        glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    
    glBindVertexArray(0);
    
    MouseLogs::glCheckError();
}
