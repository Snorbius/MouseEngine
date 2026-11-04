#include "InputManager.h"

#include <GLFW/glfw3.h>

bool InputManager::IsKeyPressedDown(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}
