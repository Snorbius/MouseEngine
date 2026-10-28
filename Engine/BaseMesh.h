#pragma once
#include <vector>

#include "Renderable.h"
#include "Transform.h"

class BaseMesh: public Renderable
{
public:
    BaseMesh();
    ~BaseMesh() override;
    
private:
    const int floatsPerVertex = 3;
    int vertexCount = 0;
    
protected:
    unsigned int vbo;
    unsigned int vao;
    
    void UpdateVertexData(float data[], int size);
    void UpdateVertexData(const std::vector<float>& data);
    
public:
    Transform transform;
    
    void Render(Shader* shader) override;
};
