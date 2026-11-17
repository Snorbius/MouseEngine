#pragma once
#include <map>
#include <vector>

class Renderable;
class Material;

class BaseRenderer
{
private:
    std::map<Material*, std::vector<Renderable*>> objectsToRender;
    std::map<Renderable*, Material*> renderableMaterialMap;
    
public:
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
};
