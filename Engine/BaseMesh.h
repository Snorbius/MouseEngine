#pragma once
#include <vector>

#include "Renderable.h"

class BaseMesh: public Renderable
{
public:
    BaseMesh();
    ~BaseMesh() override;
    
private:
    const int floatsPerVertex = 6;
    int vertexCount = 0;
    
protected:
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;

public:
    /** Whether to use indices for rendering */
    bool useEbo = false;
    
    /**
     * Updates the vertex data for the mesh. This function is intended for non-ebo usage.
     * @param data The vertex data.
     * @param size The size of the data array.
     */
    void UpdateVertexData(const float* data, int size);
    void UpdateVertexData(const std::vector<float>& data);
    /**
     * Updates the vertex data for the mesh, given the vertex data and associated index array.
     * This function is intended for ebo usage. Make sure useEbo is set to true.
     * @param vertexData    The vertex data.
     * @param indices       The indices.
     * @param dataSize      The size of the data array.
     * @param indicesSize   The size of the indices array.
     */
    void UpdateVertexData(const float* vertexData, const int* indices, int dataSize, int indicesSize);
    void UpdateVertexData(const std::vector<float>& vertexData, const std::vector<int>& indices);
    
    void Render(Shader* shader) override;
};
