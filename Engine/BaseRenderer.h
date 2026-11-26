#pragma once
#include <map>
#include <vector>
#include <glm/vec4.hpp>

class MouseEngineContext;
class Renderable;
class Material;

class BaseRenderer
{
public:
    BaseRenderer();
    
private:
    MouseEngineContext* EngineContext;
    
    std::map<Material*, std::vector<Renderable*>> objectsToRender;
    std::map<Renderable*, Material*> renderableMaterialMap;
    
    glm::vec4 clearColor = glm::vec4(1.0f, 0.9f, 1.0f, 1.0f);
    glm::ivec4 viewport;
    
public:
    void ClearScreen();
    
    /**
     * Renders the screen.
     */
    void RenderScreen();

    /**
     * Registers a renderable to be rendered with a specified material.
     * @param renderable The object to render.
     * @param material The material to render the object with. Leaving this at null with instead use a fallback material.
     */
    void RegisterRenderable(Renderable* renderable, Material* material);

    /**
     * Unregisters an object to no longer be rendered.
     * @param renderable The object to unregister.
     */
    void UnregisterRenderable(Renderable* renderable);

    /**
     * Sets the color used when clearing the screen.
     * @param color The color.
     */
    void SetClearColor(glm::vec4 color);

    /**
     * Sets the viewport dimensions. This will also scissor using the same dimensions.
     * @param x The x position
     * @param y The y position
     * @param width The width
     * @param height The height
     */
    void SetViewportDimensions(int x, int y, int width, int height);

    /**
     * Clears the entire screen using the current clear color.
     * Scissor testing is temporarily disabled to achieve this.
     */
    void ClearEntireScreen();
    
    void RenderComponents();
};
