#include "Shader.h"

#include <format>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#include "LogManager.h"
#include "Transform.h"

using namespace MouseLogs;

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    Initialize(vertexPath, fragmentPath);
}

std::string Shader::ReadFile(std::string input)
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

unsigned int Shader::LoadShader(const char* source, GLenum type)
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
        print_warning(std::format("Could not compile shader source: {}", log));
    }
    
    return id;
}

int Shader::GetUniformIndex(const std::string& name)
{
    // Just grab the uniform location from the vector if it exists
    for (std::tuple uniform : uniforms)
        if (std::get<0>(uniform) == name)
            return std::get<1>(uniform);
    
    int index = glGetUniformLocation(programId, name.c_str());
    // Returning -1 is still fine, opengl will simply silently ignore it
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
    if (index == -1)
        print_warning(std::format("Tried accessing uniform \"{}\" that does not exist.", name));
    else
        uniforms.emplace_back(name, index); // Add the location to the known uniforms
        
    return index;
}

int Shader::Initialize(std::string vertexPath, std::string fragmentPath)
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
        print_warning(std::format("Could not link shader program: {}", log));
        return -1;
    }
    
    return 0;
}

void Shader::SetUniform(const std::string& name, float value)
{
    glProgramUniform1f(programId, GetUniformIndex(name), value);
}

void Shader::SetUniform(const std::string& name, float x, float y)
{
    glProgramUniform2f(programId, GetUniformIndex(name), x, y);
}

void Shader::SetUniform(const std::string& name, glm::vec2 value)
{
    glProgramUniform2fv(programId, GetUniformIndex(name), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, float x, float y, float z)
{
    glProgramUniform3f(programId, GetUniformIndex(name), x, y, z);
}

void Shader::SetUniform(const std::string& name, glm::vec3 value)
{
    glProgramUniform3fv(programId, GetUniformIndex(name), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, float x, float y, float z, float w)
{
    glProgramUniform4f(programId, GetUniformIndex(name), x, y, z, w);
}

void Shader::SetUniform(const std::string& name, glm::vec4 value)
{
    glProgramUniform4fv(programId, GetUniformIndex(name), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, const Transform& transform)
{
    glProgramUniformMatrix3fv(programId, GetUniformIndex(name), 1, false, transform.data);
}

void Shader::Use() const
{
    glUseProgram(programId);
}
