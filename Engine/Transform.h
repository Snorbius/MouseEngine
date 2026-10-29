#pragma once

#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

class Transform
{
public:
    Transform();
    
private:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::mat4 transformMatrix;
    
    void UpdateData();
    
public:
    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetScale() const { return scale; }
    glm::vec3 GetRotation() const { return rotation; }
    glm::mat4 GetTransformMatrix() const { return transformMatrix; }
    
    void SetPosition(glm::vec3 value);
    void SetScale(glm::vec3 value);
    void SetRotation(glm::vec3 value);
};
