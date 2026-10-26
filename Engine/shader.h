#pragma once
#include <string>
#include <glad/glad.h>

class shader
{
public:
    shader(std::string vertexPath, std::string fragmentPath);

private:
    unsigned int programId = 0;

    static std::string ReadFile(std::string input);
    static unsigned int LoadShader(const char* source, GLenum type);
  
public:
    int Initialize(std::string vertexPath, std::string fragmentPath);
    void Use() const;
};
