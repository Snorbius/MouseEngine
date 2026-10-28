#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/LogManager.h"
#include "Engine/Shader.h"
#include "Engine/Content/Meshes/TriangleMesh.h"

using namespace MouseLogs;

int main()
{
    if (!glfwInit())
    {
        print_error("Failed to initialize GLFW");
        return -1;
    }
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mouse Engine", nullptr, nullptr);
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        print_error("Failed to initialize GLAD");
        return -1;
    } 
    
    Shader shader(R"(C:\code\cpp\MouseEngine\Engine\Content\Shaders\basic_vertex.vert)",
                  R"(C:\code\cpp\MouseEngine\Engine\Content\Shaders\basic_fragment.frag)");
    
    shader.SetUniform("u_color", 1.0f, 0.0f, 0.0f, 1.0f);
    
    TriangleMesh triangle;
    
    while (!glfwWindowShouldClose(window))
    {
        float time = static_cast<float>(glfwGetTime());
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        glClearColor(1.0f, 0.9f, 1.0f, 1.0f);
        
        float s = (sinf(time * 0.25f) + 1.0f) / 2.0f;
        s *= 0.25f;
        
        triangle.transform.SetScale(glm::vec3(0.25f + s));
        triangle.transform.SetRotation(glm::vec3(powf(time * 0.3f, 3)));
        
        triangle.Render(&shader);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    return 0;
}
