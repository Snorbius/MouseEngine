#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/LogManager.h"
#include "Engine/Shader.h"

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
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glClearColor(1.0f, 0.9f, 1.0f, 1.0f);
        
        float vertices[] = {
            -0.5f, -0.3f, 0.0f,
            0.5f, -0.3f, 0.0f,
            0.0f, 0.8f, 0.0f,
        };
        
        unsigned int VAO;
        unsigned int VBO;
        
        // Generate objects
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        
        // Bind array object
        glBindVertexArray(VAO);
        
        // Bind buffer object (makes it active)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        // Buffers data into the active buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        // Tells opengl how to interpret our vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, static_cast<void*>(0));
        glEnableVertexAttribArray(0);
        
        shader.Use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    return 0;
}
