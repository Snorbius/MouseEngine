#pragma once
#include "Transform.h"
#include "Interfaces/IKeyboardInputCallback.h"

class BaseCamera: IKeyboardInputCallback
{
public:
    BaseCamera();
    
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
    bool InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
};
