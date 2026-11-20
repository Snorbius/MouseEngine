#pragma once
#include <glm/vec2.hpp>
// #include <GLFW/glfw3.h>

struct GLFWwindow;

class InputManager
{
public:
    explicit InputManager(GLFWwindow* window);

private:
    GLFWwindow* window;
    glm::dvec2 lastMousePos;
    glm::dvec2 deltaMousePos;
    
    bool mouseVisible = true;
    bool mouseCaptured = false;
    
    void UpdateMouseStatus();
    
    void Update();
    friend class MouseEngineContext;
    
public:
    /**
     * Checks whether a given key is pressed down.
     * @param key Key. Make use of GLFW_KEY_* macros.
     * @return Whether it was pressed down.
     */
    bool IsKeyPressedDown(int key) const;

    /**
     * Gets the axis values of currently connected controllers.
     * @param controllerIndex The index of the controller.
     * @param stickIndex The index of the joystick (typically 0 would be left stick, 1 right).
     * @param deadzone How large the deadzone should be. Defaults to 0.2.
     * @return The axis values.
     */
    glm::vec2 GetControllerAxisValue(int controllerIndex, int stickIndex, float deadzone = 0.2f);
    
    glm::vec2 GetCurrentMousePos() const { return lastMousePos; }
    glm::vec2 GetDeltaMousePos() const { return deltaMousePos; }
    bool GetMouseVisible() const { return mouseVisible; }
    bool GetMouseCaptured() const { return mouseCaptured; }
    
    void SetMouseVisibility(bool value);
    void SetMouseCaptured(bool value);
};
