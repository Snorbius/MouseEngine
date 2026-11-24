#include "Object3D.h"

#include "MouseEngineContext.h"
#include "ECS/ComponentSystem.h"

Object3D::Object3D()
{
    EngineContext->Components->AddComponent<Transform>(this);
    transform = *EngineContext->Components->GetComponent<Transform>(this);
}
