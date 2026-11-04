#include "Object.h"

#include "MouseEngineContext.h"

Object::Object()
{
    EngineContext = MouseEngineContext::GetInstance();
    
    if (processEnabled)
        EngineContext->RegisterForProcess(this);
}

Object::~Object()
{
    if (processEnabled)
        EngineContext->UnRegisterForProcess(this);
}

void Object::SetProcessEnabled(bool value)
{
    // Do nothing if process mode doesn't change
    if (processEnabled == value)
        return;
    
    processEnabled = value;
    if (processEnabled)
        EngineContext->RegisterForProcess(this);
    else
        EngineContext->UnRegisterForProcess(this);
}
