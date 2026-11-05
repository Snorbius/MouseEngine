#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "LogManager.h"
#include "Temporary/AssessmentHouse.h"

class InputManager;
class TimeManager;

class Object;
class IKeyboardInputCallback;
using namespace MouseLogs;

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600
#define DEFAULT_WINDOW_NAME "Mouse Engine"

class MouseEngineContext
{
public:
    MouseEngineContext(MouseEngineContext& context) = delete;
    void operator=(const MouseEngineContext&) = delete;
    
    /** Fetch the engine context instance */
    static MouseEngineContext* GetInstance();
    std::vector<Object*> processObjects;
    std::vector<IKeyboardInputCallback*> inputObjects;
    
private:
    GLFWwindow* contextWindow = nullptr;
    AssessmentHouse* house;
    bool wireframe = false;
    
    bool InitialiseGLFW();
    bool InitialiseGLAD();
    bool InitialiseDebugContext();
    void ToggleWireframe();
    
    void HandleProcess();
    
protected:
    static inline MouseEngineContext* engineContextInstance;
    static void StaticInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    MouseEngineContext();
    ~MouseEngineContext();
    
public:
    TimeManager* Time;
    InputManager* Input;
    
    /** Starts the full engine loop */
    void EngineLoop();

    /**
     * Registers an object for receiving input.
     * 
     * @param object The object to register.
     */
    void RegisterForInput(IKeyboardInputCallback* object);

    /**
     * Registers the object to receive a process call every engine tick.
     * NOTE: This should not be called manually, use Object::SetProcessEnabled instead.
     * @param object The object to enable process for.
     */
    void RegisterForProcess(Object* object);
    
    /**
     * Unregisters the object from receiving a process call every engine tick.
     * NOTE: This should not be called manually, use Object::SetProcessEnabled instead.
     * @param object The object to disable process for.
     */
    void UnRegisterForProcess(Object* object);

    /**
     * Returns whether the application has focus or not.
     * @return Whether it has focus
     */
    bool HasFocus() const;
};
