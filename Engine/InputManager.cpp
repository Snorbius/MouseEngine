#include "InputManager.h"

#include <algorithm>
#include <GLFW/glfw3.h>

InputManager::InputManager(GLFWwindow* window): window(window)
{
    glfwGetCursorPos(window, &lastMousePos.x, &lastMousePos.y);
}

void InputManager::UpdateMouseStatus()
{
    int mode = GLFW_CURSOR_NORMAL;
    
    if (mouseVisible && mouseCaptured)
        mode = GLFW_CURSOR_CAPTURED;
    if (mouseVisible && !mouseCaptured)
        mode = GLFW_CURSOR_NORMAL;
    if (!mouseVisible && mouseCaptured)
        mode = GLFW_CURSOR_DISABLED;
    if (!mouseVisible && !mouseCaptured)
        mode = GLFW_CURSOR_HIDDEN;
            
    glfwSetInputMode(window, GLFW_CURSOR, mode);
    
    glfwGetCursorPos(window, &lastMousePos.x, &lastMousePos.y);
}

void InputManager::Update()
{
    glm::dvec2 currentMousePos;
    glfwGetCursorPos(window, &currentMousePos.x, &currentMousePos.y);
    deltaMousePos = currentMousePos - lastMousePos;
    lastMousePos = currentMousePos;
}

bool InputManager::IsKeyPressedDown(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

glm::vec2 InputManager::GetControllerAxisValue(int controllerIndex, int stickIndex, float deadzone)
{
    glm::vec2 result = glm::vec2(0);
    
    int count;
    const float* joystickInput = glfwGetJoystickAxes(GLFW_JOYSTICK_1 + std::min(controllerIndex, 4), &count);

    if (count < stickIndex * 2 - 1 || joystickInput == nullptr)
        return result;
    
    result.x = joystickInput[static_cast<size_t>(stickIndex * 2)];
    result.y = joystickInput[static_cast<size_t>(stickIndex * 2 + 1)];
    
    if (abs(result.x) < deadzone)
        result.x = 0;
    if (abs(result.y) < deadzone)
        result.y = 0;
    
    return result;
}

void InputManager::SetMouseVisibility(bool value)
{
    if (mouseVisible == value)
        return;
    
    mouseVisible = value;
    UpdateMouseStatus();
}

void InputManager::SetMouseCaptured(bool value)
{
    if (mouseCaptured == value)
        return;
    
    mouseCaptured = value;
    UpdateMouseStatus();
}
