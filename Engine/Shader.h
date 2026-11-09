#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/ext/matrix_float4x4.hpp>

class Transform;

struct ShaderStruct
{
    std::string vertexPath;
    std::string fragmentPath;
    
    bool operator==(const ShaderStruct& other) const
    {
        return vertexPath == other.vertexPath && fragmentPath == other.fragmentPath;
    }
    
    bool operator<(const ShaderStruct& other) const
    {
        return vertexPath < other.vertexPath;
    }
};

class Shader
{
public:
    Shader(const ShaderStruct& shader);
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

private:
    unsigned int programId = 0;
    
    // <uniform_name, uniform_location>
    std::vector<std::tuple<std::string, int>> uniforms;

    static std::string ReadFile(const std::string& input);
    static unsigned int LoadShader(const char* source, GLenum type);
    
    int GetUniformIndex(const std::string& name);
  
public:
    /**
     * Initializes the shader. Gets called automatically on construct but is here for re-initialization.
     * @param vertexPath Path to the vertex shader
     * @param fragmentPath Path to the fragment shader
     * @return 0 if successful, -1 otherwise
     */
    int Initialize(const std::string& vertexPath, const std::string& fragmentPath);

    /** Sets the specified uniform with the specified value. It is NOT necessary to bind the shader first.
     * You can probably figure out the value type based on the parameters :)) */
    void SetUniform(const std::string& name, float value);
    void SetUniform(const std::string& name, float x, float y);
    void SetUniform(const std::string& name, glm::vec2 value);
    void SetUniform(const std::string& name, float x, float y, float z);
    void SetUniform(const std::string& name, glm::vec3 value);
    void SetUniform(const std::string& name, float x, float y, float z, float w);
    void SetUniform(const std::string& name, glm::vec4 value);
    void SetUniform(const std::string& name, glm::mat4 value);
    
    /** Binds the shader in the current gl context */
    void Use() const;
};
