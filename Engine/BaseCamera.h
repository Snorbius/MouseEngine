#pragma once
#include "Object.h"
#include "Transform.h"

class BaseCamera: public Object
{
public:
    BaseCamera() = default;
    
private:
    glm::vec3 up = glm::vec3(0, 1, 0);
    float fov = 45.0f;
    float aspectRatio = 2560.0f / 1440.0f;
    float nearPlane = 0.01f;
    float farPlane = 100.0f;
    
public:
    Transform transform;
    
    float GetFov() const { return fov; }
    float GetAspectRatio() const { return aspectRatio; }
    glm::vec2 GetNearFarPlane() const { return {nearPlane, farPlane}; }
    glm::mat4 GetView() const;
    glm::mat4 GetProjection() const;
    
    void SetAspectRatio(float ratio);
    void SetAspectRatio(float width, float height) { SetAspectRatio(width / height); }
    
    void Process(float deltaTime) override;
};
