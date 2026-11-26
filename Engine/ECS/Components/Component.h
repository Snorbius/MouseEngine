#pragma once
#include "../EntityManager.h"
#include "../../MouseEngineContext.h"

class MouseEngineContext;

struct Component
{
private:
    Entity GetEntity();
    
protected:
    MouseEngineContext* EngineContext = MouseEngineContext::GetInstance();
};
