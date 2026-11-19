#include "IKeyboardInputCallback.h"

#include "../MouseEngineContext.h"

IKeyboardInputCallback::~IKeyboardInputCallback()
{
    MouseEngineContext::GetInstance()->UnregisterForInput(this);
}

bool IKeyboardInputCallback::InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    return false;
}
