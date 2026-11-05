#include "InputManager.h"

#include <GLFW/glfw3.h>

InputManager::InputManager(GLFWwindow* window): window(window)
{
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
