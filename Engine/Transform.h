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
    
    glm::vec3 forward = glm::vec3(0, 0, 1);
    glm::vec3 right = glm::vec3(1, 0, 0);
    glm::vec3 up = glm::vec3(0, 1, 0);
    
    void UpdateData();
    void UpdateAxisVectors();
    
public:
    glm::vec3 GetPosition() const           { return position; }
    glm::vec3 GetScale() const              { return scale; }
    glm::vec3 GetRotation() const           { return rotation; }
    glm::vec3 GetForward() const            { return forward; }
    glm::vec3 GetRight() const              { return right; }
    glm::vec3 GetUp() const                 { return up; }
    glm::mat4 GetTransformMatrix() const    { return transformMatrix; }
    
    void SetPosition(glm::vec3 value);
    void Translate(glm::vec3 value);
    void SetScale(glm::vec3 value);
    void SetScale(float uniformScale);
    void SetRotation(glm::vec3 value);
    void Rotate(glm::vec3 value);
    void PointAt(glm::vec3 targetPosition);
};
