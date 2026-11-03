#pragma once

struct GLFWwindow;

class IKeyboardInputCallback
{
public:
    virtual ~IKeyboardInputCallback() {}
    
    /** Called when the player performs a keyboard input. You must first register the object for input, 
     * see EngineContext::RegisterForInput.
     * 
     * The return value specifies whether the input was handled.
     */
    virtual bool InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
