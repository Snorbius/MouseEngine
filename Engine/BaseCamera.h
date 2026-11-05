#pragma once
#include "Object.h"
#include "Transform.h"
#include "Interfaces/IKeyboardInputCallback.h"

class BaseCamera: public Object, IKeyboardInputCallback
{
public:
    BaseCamera();
    
private:
    glm::vec3 up = glm::vec3(0, 1, 0);
    float fov = 45.0f;
    float aspectRatio = 2560.0f / 1440.0f;
    float nearPlane = 0.01f;
    float farPlane = 100.0f;
    bool orthographic = false;
    
    void HandleMovement(float deltaTime);
    void HandleLook(float deltaTime);
    
public:
    Transform transform;
    
    /** Get the current field of view for this camera. Only has an effect if the camera is in perspective mode (not orthographic). */
    float GetFov() const { return fov; }
    /** Get the current aspect ratio for this camera. */
    float GetAspectRatio() const { return aspectRatio; }
    /** Get the current near and far plane for this camera. */
    glm::vec2 GetNearFarPlane() const { return {nearPlane, farPlane}; }
    /** Get a view matrix based on the cameras position. */
    glm::mat4 GetView() const;
    /** Get a projection matrix for this camera. Is affected by the current orthographic property value. */
    glm::mat4 GetProjection() const;
    /** Get whether the camera is currently in orthographic mode (perspective otherwise) */
    bool GetIsOrthographic() const { return orthographic; }
    /** Set the projection mode for the camera. True means orthographic, false means perspective. */
    void SetIsOrthographic(bool value);
    /** Sets the current aspect ratio */
    void SetAspectRatio(float ratio);
    void SetAspectRatio(float width, float height) { SetAspectRatio(width / height); }
    
    void Process(float deltaTime) override;
    
    bool InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
};
