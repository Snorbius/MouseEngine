#pragma once

class TimeManager
{
public:
    TimeManager() = default;
    
private:
    double lastTime = 0.0f;
    double deltaTime = 0.0f;
    float timeScale = 1.0f;
    double time;
    
    void Update();
    
    friend class MouseEngineContext;
    
protected:
    
public:
    double GetWorldDeltaTime() const { return deltaTime; }
    float GetWorldDeltaTimef() const { return static_cast<float>(deltaTime); }
    double GetTotalElapsedTime() const { return time; }
    float GetTotalElapsedTimef() const { return static_cast<float>(time); }
};

