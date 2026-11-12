#include "InputManager.h"

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
