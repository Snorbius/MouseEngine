#include "Material.h"

#include "../AssetManager.h"
#include "../MouseEngineContext.h"
#include "../Texture.h"

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
}
