#pragma once
#include <numbers>
#include <string>
#include <glad/glad.h>

struct Transform
{
    float position[3] = {0.0f, 0.0f, 0.0f};
    float scale[3] = {1.0f, 1.0f, 1.0f};
    float rotation[3] = {0.0f, 0.0f, 0.0f};
    
    void SetPos(float x, float y, float z)
    {
        position[0] = x;
        position[1] = y;
        position[2] = z;
    }
    
    void SetScale(float x, float y, float z)
    {
        scale[0] = x;
        scale[1] = y;
        scale[2] = z;
    }
    
    void SetRot(float x)
    {
        rotation[0] = x * (std::numbers::pi_v<float> / 180.0f);
    }
};

class Shader
{
public:
    Shader(std::string vertexPath, std::string fragmentPath);

private:
    unsigned int programId = 0;

    static std::string ReadFile(std::string input);
    static unsigned int LoadShader(const char* source, GLenum type);
    
    int GetUniformIndex(const std::string& name);
  
public:
    /**
     * Initializes the shader. Gets called automatically on construct but is here for re-initialization.
     * @param vertexPath Path to the vertex shader
     * @param fragmentPath Path to the fragment shader
     * @return 0 if successful, -1 otherwise
     */
    int Initialize(std::string vertexPath, std::string fragmentPath);

    /** Sets the specified uniform with the specified value. It is NOT necessary to bind the shader first.
     * You can probably figure out the value type based on the parameters :)) */
    void SetUniform(const std::string& name, float value);
    void SetUniform(const std::string& name, float x, float y);
    void SetUniform(const std::string& name, float x, float y, float z);
    void SetUniform(const std::string& name, float x, float y, float z, float w);
    void SetUniform(const std::string& name, Transform transform);
    
    /** Binds the shader in the current gl context */
    void Use() const;
};
