#include "shader.h"

#include <format>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>

shader::shader(std::string vertexPath, std::string fragmentPath)
{
    Initialize(vertexPath, fragmentPath);
}

std::string shader::ReadFile(std::string input)
{
    std::string source;
    std::ifstream file;
    
    file.open(input);
    
    std::stringstream stream;
    stream << file.rdbuf();
    
    file.close();
    source = stream.str();
    
    return source;
}

unsigned int shader::LoadShader(const char* source, GLenum type)
{
    int result;
    char log[512];
    
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (!result)
    {
        glGetShaderInfoLog(id, 512, nullptr, log);
        // TODO: Print warning
        std::cout << std::format("Warning: Could not compile shader source: {}", log) << '\n';
    }
    
    return id;
}

int shader::Initialize(std::string vertexPath, std::string fragmentPath)
{
    int result;
    char log[512];
    
    std::string vertexSource = ReadFile(vertexPath);
    std::string fragmentSource = ReadFile(fragmentPath);
    unsigned int vertexShader = LoadShader(vertexSource.c_str(), GL_VERTEX_SHADER);
    unsigned int fragmentShader = LoadShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
    
    programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);
    
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(programId, 512, nullptr, log);
        // TODO: Print warning
        std::cout << std::format("Warning: Could not link shader program: {}", log) << '\n';
        return -1;
    }
    
    return 0;
}

void shader::Use() const
{
    glUseProgram(programId);
}
