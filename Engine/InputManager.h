#pragma once
// #include <GLFW/glfw3.h>

struct GLFWwindow;

class InputManager
{
public:
    explicit InputManager(GLFWwindow* window)
        : window(window)
    {
    }

private:
    GLFWwindow* window;
    
public:
    /**
     * Checks whether a given key is pressed down.
     * @param key Key. Make use of GLFW_KEY_* macros.
     * @return Whether it was pressed down.
     */
    bool IsKeyPressedDown(int key) const;
};
