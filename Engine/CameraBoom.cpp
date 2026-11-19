#include "CameraBoom.h"

#include "BaseCamera.h"

CameraBoom::CameraBoom()
{
    transform.SetRotation({0, -90, 0});
}

void CameraBoom::Process(float deltaTime)
{
    if (target == nullptr)
        return;
    
    transform.SetPosition(target->transform.GetPosition() + offset);

    if (camera == nullptr)
        return;
    
    camera->transform.SetPosition(transform.GetPosition() - transform.GetForward() * targetRange);
    // camera->transform.PointAt(target->transform.GetPosition());
    
    // transform.Rotate(glm::vec3(0, 1, 0) * 45.0f * deltaTime);
    
    camera->transform.SetRotation(transform.GetRotation());
}
