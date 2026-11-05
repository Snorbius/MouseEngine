#pragma once
#include <string>

class Texture
{
public:
    /**
     * Constructs a texture based on an image path.
     * @param imagePath The path to the image.
     */
    Texture(const std::string& imagePath);
    
private:
    unsigned int textureObject = 0;
    int channels = 0;
    int width = 0;
    int height = 0;
    
    
public:
    /** Gets the width of the texture. */
    int GetWidth() const { return  width; }
    /** Gets the height of the texture. */
    int GetHeight() const { return  height; }
    
    /**
     * Loads an image into the texture. This will override any existing image already there.
     * The texture can load an image during its construction so make sure you only call this when you intend to.
     * @param imagePath The path to the image.
     */
    void LoadImage(const std::string& imagePath);
    
    /** Binds the texture and makes it active. */
    void Use();
};
