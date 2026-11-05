#include "Texture.h"

#include <format>

#include "LogManager.h"
#include "../stbi/stbi_image.h"

Texture::Texture(const std::string& imagePath)
{
    glGenTextures(1, &textureObject);
    LoadImage(imagePath);
}

void Texture::LoadImage(const std::string& imagePath)
{
    auto data = stbi_load(imagePath.c_str(), &width, &height, &channels, 4);
    
    if (!data)
    {
        MouseLogs::print_warning(std::format(
            "Image from path {} could not be loaded: {}", imagePath, stbi_failure_reason()));
        return;
    }

    glBindTexture(GL_TEXTURE_2D, textureObject);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
        GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Use()
{
    glBindTexture(GL_TEXTURE_2D, textureObject);
}
