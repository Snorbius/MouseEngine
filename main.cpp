#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/LogManager.h"
#include "Engine/Shader.h"
#include "Engine/Content/Meshes/TriangleMesh.h"
#include "Engine/Temporary/AssessmentHouse.h"

using namespace MouseLogs;

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

float time;
AssessmentHouse* house;

int main()
{
    if (!glfwInit())
    {
        print_error("Failed to initialize GLFW");
        return -1;
    }
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mouse Engine", nullptr, nullptr);
    
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, InputCallback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        print_error("Failed to initialize GLAD");
        return -1;
    } 
    
    Shader shader(R"(C:\code\cpp\MouseEngine\Engine\Content\Shaders\basic_vertex.vert)",
                  R"(C:\code\cpp\MouseEngine\Engine\Content\Shaders\basic_fragment.frag)");
    
    // shader.SetUniform("u_color", 1.0f, 0.0f, 0.0f, 1.0f);
    shader.SetUniform("u_color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    
    house = new AssessmentHouse();
    
    while (!glfwWindowShouldClose(window))
    {
        time = static_cast<float>(glfwGetTime());
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
