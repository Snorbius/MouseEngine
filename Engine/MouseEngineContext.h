#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "LogManager.h"
#include "ImGuiWindows/EngineUI.h"

class FlyingPlayer;
class Scene;
class FlyingPlayerWithCamera;
class BaseCamera;
class BaseRenderer;
class AssetManager;
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
    
    glm::ivec2 framebufferSize = glm::ivec2(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    
    BaseCamera* activeCamera; 
    
    int numPlayers = 1;
    
private:
    GLFWwindow* contextWindow = nullptr;
    bool wireframe = false;
    
    std::vector<FlyingPlayerWithCamera*> players;
    
    Scene* ActiveScene = nullptr;
    
    bool InitialiseGLFW();
    bool InitialiseGLAD();
    bool InitialiseDebugContext();
    void ToggleWireframe();
    void InitialiseImGui();
    
    void HandleProcess();
    void RespawnPlayer(FlyingPlayer* player);
    void RenderImGui(EngineUI* engineUI);

protected:
    static inline MouseEngineContext* engineContextInstance;
    static void StaticInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void StaticResizeCallback(GLFWwindow* window, int width, int height);
    void ResizeCallback(GLFWwindow* window, int width, int height);
    
    MouseEngineContext();
    ~MouseEngineContext();
    
public:
    TimeManager* Time;
    InputManager* Input;
    AssetManager* Assets;
    BaseRenderer* Renderer;
    
    /** Starts the full engine loop */
    void EngineLoop();

    /**
     * Registers an object for receiving input.
     * 
     * @param object The object to register.
     */
    void RegisterForInput(IKeyboardInputCallback* object);

    /**
     * Unregisters an object for keyboard input callbacks.
     * @param object The object to unregister.
     */
    void UnregisterForInput(IKeyboardInputCallback* object);
    
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

    /**
     * Loads a scene and makes it the currently active one. This will also delete/unload the previous active scene.
     * @param scenePath The path to the scene.
     */
    void LoadScene(const std::string& scenePath);

    /**
     * Checks the player count and deletes/creates players based on the difference. 
     * This function is very temporary teehee.
     */
    void RefreshPlayerCount();
};
