#include "InputManager.h"

#include <algorithm>
#include <format>
#include <GLFW/glfw3.h>

#include "TimeManager.h"

InputManager::InputManager(GLFWwindow* window): window(window)
{
    glfwGetCursorPos(window, &lastMousePos.x, &lastMousePos.y);
    
    Time = MouseEngineContext::GetInstance()->Time;
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

void InputManager::Update(float deltaTime)
{
    glm::dvec2 currentMousePos;
    glfwGetCursorPos(window, &currentMousePos.x, &currentMousePos.y);
    deltaMousePos = currentMousePos - lastMousePos;
    lastMousePos = currentMousePos;

    float time = Time->GetTotalElapsedTimef();
    for (std::pair<const int, float>& key : keyMap)
    {
        
        
        if (key.second > 0 && keyCallbacks[HELD].contains(key.first))
        {
            for (const std::function<void(float)>& func : keyCallbacks[HELD][key.first])
                func(time - key.second);
        }
    }
}

void InputManager::InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        keyMap[key] = Time->GetTotalElapsedTimef();
        
        if (!keyCallbacks[PRESSED].contains(key))
            return;

        for (const std::function<void(float)>& func : keyCallbacks[PRESSED][key])
            func(0);
    }
    
    if (action == GLFW_RELEASE)
    {
        if (keyCallbacks[RELEASED].contains(key))
            for (const std::function<void(float)>& func : keyCallbacks[RELEASED][key])
                func(0);

        keyMap[key] = -1;
    }
}

bool InputManager::IsKeyHeld(int key)
{
    return keyMap.contains(key) && keyMap[key] > 0;
}

bool InputManager::IsKeyPressed(int key)
{
    return keyMap.contains(key) && abs(keyMap[key] - Time->GetTotalElapsedTimef()) < 0.001;
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

void InputManager::RegisterInputFunction(int key, KEY_STATUS status, const std::function<void(float duration)>& func)
{
    if (!keyCallbacks[status].contains(key))
        keyCallbacks[status][key] = {};
    
    keyCallbacks[status][key].emplace_back(func);
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
