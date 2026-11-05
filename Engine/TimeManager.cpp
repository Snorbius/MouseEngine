#include "TimeManager.h"

#include <GLFW/glfw3.h>

void TimeManager::Update()
{
    double current = glfwGetTime();
    deltaTime = current - lastTime;
    lastTime = current;
    
    time += deltaTime;
}
