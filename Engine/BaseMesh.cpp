#include "BaseMesh.h"

#include <glad/glad.h>

#include "LogManager.h"
#include "Shader.h"

void BaseMesh::UpdateVertexData(float data[], int size)
{
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
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(data.size() * sizeof(float)), data.data(), GL_STATIC_DRAW);

    int numFloats = static_cast<int>(data.size());
    if (numFloats % floatsPerVertex != 0)
        MouseLogs::print_warning("Size of data does not match attribute configuration");
    
    vertexCount = numFloats / floatsPerVertex;
}

BaseMesh::BaseMesh()
{
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

BaseMesh::~BaseMesh()
{
    if (vao)
        glDeleteVertexArrays(1, &vao);
    if (vbo)
        glDeleteBuffers(1, &vbo);
}

void BaseMesh::Render(Shader* shader)
{
    shader->SetUniform("u_transform", transform);
    
    shader->Use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
    
    MouseLogs::glCheckError();
}
