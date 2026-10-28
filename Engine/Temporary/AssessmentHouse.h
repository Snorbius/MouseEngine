#pragma once

#include <glm/vec4.hpp>

#include "../Content/Meshes/TriangleMesh.h"

class AssessmentHouse: public Renderable
{
private:
    glm::vec4 roofColor = glm::vec4(0.992f, 0.882f, 0.176f, 1.0f);
    
    void DrawTriangle(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, glm::vec4 color, Shader* shader);
    void DrawRectangle(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, glm::vec4 color, Shader* shader);
    
public:
    TriangleMesh triangleMesh;
    bool roofswap = false;
    
    void Render(Shader* shader) override;
    void SwapRoofColor();
    
    float time;
};
