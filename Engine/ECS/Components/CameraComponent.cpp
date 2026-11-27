#include "CameraComponent.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "TransformComponent.h"
#include "../../MouseEngineContext.h"

glm::mat4 CameraComponent::GetView() const
{
    TransformComponent trans;
    TryGetSiblingComponent<TransformComponent>(trans);
    glm::vec3 pos2 = trans.GetPosition();
    return glm::lookAt(pos2, pos2 + trans.GetForward(), glm::vec3(0, 1, 0));
}

glm::mat4 CameraComponent::GetProjection() const
{
    const float orthosize = 6;
    
    if (!orthographic)
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
        
    // return glm::ortho(-orthosize * aspectRatio, orthosize * aspectRatio, -orthosize, orthosize, nearPlane, farPlane);
       
    float left = -orthosize * aspectRatio;
    float right = orthosize * aspectRatio;
    float bottom = -orthosize;
    float top = orthosize;
    float near = nearPlane;
    float far = farPlane;
    
    
    float sx = 2.0f / (right - left);   // Converts the X axis to a range of 2
    float sy = 2.0f / (top - bottom);   // Converts the Y axis to a range of 2
    float sz = 2.0f / (far - near);     // Converts the Z axis to a range of 2
    
    float tx = - (right + left) / (right - left);    // Offsets the X axis to be between -1 and 1
    float ty = - (top + bottom) / (top - bottom);    // Offsets the Y axis to be between -1 and 1
    float tz = - (far + near)   / (far - near);      // Offsets the Z axis to be between -1 and 1
    
    // Transposed to match opengls ordering
    return glm::transpose(glm::mat4(
        sx,         0.0f,       0.0f,       tx,
        0.0f,       sy,         0.0f,       ty,
        0.0f,       0.0f,       -sz,        tz,
        0.0f,       0.0f,       0.0f,       1.0f
    ));
}

void CameraComponent::SetIsOrthographic(bool value)
{
    orthographic = value;
}

void CameraComponent::SetAspectRatio(float ratio)
{
    aspectRatio = ratio;
}

void CameraComponent::MakeActive()
{
    // EngineContext->activeCamera = this;
}