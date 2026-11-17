#include "Material.h"

#include "../AssetManager.h"
#include "../MouseEngineContext.h"
#include "../Texture.h"

Material* Material::fallbackMaterial;

void Material::InitializeResource()
{
    if (!values.contains("vertexPath")
        || !values.contains("fragmentPath"))
    {
        print_warning("Material failed to initialize properly ");
    }
    
    MouseEngineContext* engineContext = MouseEngineContext::GetInstance();
    
    std::string vertexPath = values["vertexPath"];
    std::string fragmentPath = values["fragmentPath"];
    std::string texturePath = values.contains("texturePath") ? values["texturePath"] : "";
    
    shader = engineContext->Assets->LoadShader({vertexPath, fragmentPath});
    if (!texturePath.empty())
        texture = engineContext->Assets->LoadTexture(texturePath);
    // TODO: Initialize material with default/placeholder texture if nothing was defined
    
    // TODO: The values map can likely be cleared at this point to save on memory
}

void Material::Use()
{
    if (shader != nullptr)
        shader->Use();
    if (texture != nullptr)
        texture->Use();
    else
        glBindTexture(GL_TEXTURE_2D, 0);
}

Material* Material::GetFallbackMaterial()
{
    if (fallbackMaterial != nullptr)
        return fallbackMaterial;
    
    // The fallback material uses hardcoded shaders to avoid issues with any shader file not being present
    const std::string vertex = "#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aUv;\n"
    "layout (location = 3) in vec3 aNormal;\n"

    "uniform mat4 u_transform;\n"
    "uniform mat4 u_view;\n"
    "uniform mat4 u_projection;\n"
  
    "out vec4 vertexColor;\n"
    "out vec2 vertexUv;\n"
    "out vec3 vertexNormal;\n"

    "void main()\n"
    "{\n"
    "    gl_Position = u_projection * u_view * u_transform * vec4(aPos, 1.0);\n"
    
    "    vertexColor = vec4(aColor, 1.0f);\n"
    "    vertexUv = aUv;\n"
    "    vertexNormal = normalize(u_transform * vec4(aNormal, 0.0)).xyz;\n"
    "}";
    
    const std::string fragment = "#version 410 core\n"
    "out vec4 FragColor;\n"

    "uniform vec4 u_color;\n"
    "uniform float u_texture_color_alpha = 0.0;\n"

    "uniform float ambientStrength = 0.20f;\n"
    "uniform vec3 sunDirection = vec3(0.7071067811865476, 0.7071067811865476, 0.0);\n"

    "uniform sampler2D texture1;\n"
  
    "in vec4 vertexColor;\n"
    "in vec2 vertexUv;\n"
    "in vec3 vertexNormal;\n"

    "void main()\n"
    "{\n"
    "    float sunStrength = max(dot(vertexNormal, sunDirection), 0.0);\n"
    "    FragColor = max(sunStrength, ambientStrength) * mix(texture(texture1, vertexUv), vertexColor, u_texture_color_alpha);\n"
    "}";
    
    fallbackMaterial = new Material();
    
    Shader* shader = new Shader(vertex, fragment, true);
    fallbackMaterial->shader = shader;
    
    MouseEngineContext::GetInstance()->Assets->RegisterShader(shader);
    
    return fallbackMaterial;
}

void Material::CleanUp()
{
    if (fallbackMaterial == nullptr)
        return;
    
    if (fallbackMaterial->shader != nullptr)
        delete fallbackMaterial->shader;
    
    delete fallbackMaterial;
}
