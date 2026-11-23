#pragma once
#include <unordered_map>
#include <glm/vec2.hpp>
// #include <GLFW/glfw3.h>
#include <functional>
#include <map>

#include "MouseEngineContext.h"

class TimeManager;
struct GLFWwindow;

enum KEY_STATUS
{
    PRESSED = 0,
    HELD = 1,
    RELEASED = 2,
};

class InputManager
{
public:
    explicit InputManager(GLFWwindow* window);

private:
    GLFWwindow* window;
    TimeManager* Time;
    glm::dvec2 lastMousePos;
    glm::dvec2 deltaMousePos;
    
    bool mouseVisible = true;
    bool mouseCaptured = false;
    
    // <key, held duration>
    std::unordered_map<int, float> keyMap;
    
    std::map<int, std::vector<std::function<void(float duration)>>> keyCallbacks[3];
    
    void UpdateMouseStatus();
    
    void Update(float deltaTime);
    
    void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend class MouseEngineContext;
    
public:
    /**
     * Checks whether a given key is held down.
     * @param key Key. Make use of GLFW_KEY_* macros.
     * @return Whether the key is held down.
     */
    bool IsKeyHeld(int key);

    /**
     * Checks whether a key is pressed. A key will only be pressed for one tick when the key is initially pressed down.
     * Use held for continous input.
     * @param key Key. Make use of GLFW_KEY_* macros.
     * @return Whether the key was just pressed.
     */
    bool IsKeyPressed(int key);

    /**
     * Gets the axis values of currently connected controllers.
     * @param controllerIndex The index of the controller.
     * @param stickIndex The index of the joystick (typically 0 would be left stick, 1 right).
     * @param deadzone How large the deadzone should be. Defaults to 0.2.
     * @return The axis values.
     */
    glm::vec2 GetControllerAxisValue(int controllerIndex, int stickIndex, float deadzone = 0.2f);

    /**
     * Registers a function to be called when a specific key is pressed/held/released.
     * @param key Which key.
     * @param status PRESSED, HELD or RELEASED.
     * @param func The function that gets called. The float parameter represents how long the key has been held for.
     */
    void RegisterInputFunction(int key, KEY_STATUS status, const std::function<void(float duration)>& func);
    
    glm::vec2 GetCurrentMousePos() const { return lastMousePos; }
    glm::vec2 GetDeltaMousePos() const { return deltaMousePos; }
    bool GetMouseVisible() const { return mouseVisible; }
    bool GetMouseCaptured() const { return mouseCaptured; }
    
    void SetMouseVisibility(bool value);
    void SetMouseCaptured(bool value);
};
