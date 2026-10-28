#pragma once

#include <glm/vec3.hpp>

class Transform
{
public:
    Transform();
    
private:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    
    void UpdateData();
    
public:
    float data[9] = {};
    
    
    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetScale() const { return scale; }
    glm::vec3 GetRotation() const { return rotation; }
    
    void SetPosition(glm::vec3 value);
    void SetScale(glm::vec3 value);
    void SetRotation(glm::vec3 value);
};
