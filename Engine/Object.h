#pragma once
#include "ECS/Entity.h"

class MouseEngineContext;

class Object: public Entity
{
public:
    Object();
    virtual ~Object();
    
private:
    bool processEnabled = true;
    
protected:
    MouseEngineContext* EngineContext;
    
public:
    /** Set whether the object should process. Process is called once every engine tick. */
    void SetProcessEnabled(bool value);
    bool GetProcessEnabled() const { return processEnabled; }
    
    /** Called every engine tick if process is enabled. */
    virtual void Process(float deltaTime) {}
};
