#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/LogManager.h"
#include "Engine/Shader.h"
#include "Engine/Content/Meshes/TriangleMesh.h"
#include "Engine/Temporary/AssessmentHouse.h"

using namespace MouseLogs;

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

AssessmentHouse* house;

int main()
{
#if DEBUG_ENABLED
    print_line("\nYou have built the engine in debug mode. Consider turning this off for any form of release build :)\n");
#endif
    
    
    if (!glfwInit()) // Initialise GLFW
    {
        print_error("Failed to initialize GLFW");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if DEBUG_ENABLED
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mouse Engine", nullptr, nullptr);
    
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, InputCallback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // Initialise GLAD
    {
        print_error("Failed to initialize GLAD");
        return -1;
    } 
    
#if DEBUG_ENABLED
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
    else
    {
        print_warning("Failed to initialise opengl debug context.");
    }
#endif
    
    Shader shader(R"(C:\code\cpp\MouseEngine\Engine\Content\Shaders\basic_vertex.vert)",
                  R"(C:\code\cpp\MouseEngine\Engine\Content\Shaders\basic_fragment.frag)");
    
    shader.SetUniform("u_color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    
    house = new AssessmentHouse();
    
    while (!glfwWindowShouldClose(window))
    {
        house->time = static_cast<float>(glfwGetTime());
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 0.9f, 1.0f, 1.0f);
        
        house->Render(&shader);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    delete house;
    
    return 0;
}

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        house->SwapRoofColor();
}
