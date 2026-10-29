#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "LogManager.h"
#include "Temporary/AssessmentHouse.h"

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
    
private:
    GLFWwindow* contextWindow;
    AssessmentHouse* house;
    bool wireframe = false;
    
    bool InitialiseGLFW();
    bool InitialiseGLAD();
    bool InitialiseDebugContext();
    void ToggleWireframe();
    
protected:
    static inline MouseEngineContext* engineContextInstance;
    static void StaticInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    MouseEngineContext();
    ~MouseEngineContext();
    
public:
    /** Starts the full engine loop */
    void EngineLoop();
};
