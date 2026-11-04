#pragma once

class MouseEngineContext;

class Object
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
    virtual void Process(float deltaTime) = 0;
};
