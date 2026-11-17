#include "BaseRenderer.h"

#include "Resources/Material.h"

void BaseRenderer::RenderScreen()
{
    for (std::pair<Material* const, std::vector<Renderable*>>& vectorElement : objectsToRender)
    {
        vectorElement.first->Use();
        Shader* shader = vectorElement.first->shader;
        for (Renderable* renderable : vectorElement.second)
            if (renderable != nullptr)
                renderable->Render(shader);
    }
}

void BaseRenderer::RegisterRenderable(Renderable* renderable, Material* material)
{
    if (renderable == nullptr)
        return;
    
    if (material == nullptr)
        material = Material::GetFallbackMaterial();
 
    if (renderableMaterialMap.contains(renderable))
    {
        if (renderableMaterialMap[renderable] == material) // Do nothing if the renderable is already registered on this material
            return;
        
        UnregisterRenderable(renderable); // Unregister the renderable from its existing material before changing it.
    }
    
    if (!objectsToRender.contains(material))
        objectsToRender[material] = {};
    
    objectsToRender[material].push_back(renderable);
    renderableMaterialMap[renderable] = material;
}

void BaseRenderer::UnregisterRenderable(Renderable* renderable)
{
    if (!renderableMaterialMap.contains(renderable))
        return;

    std::vector<Renderable*>& v = objectsToRender[renderableMaterialMap[renderable]];

    auto index = std::ranges::find(v, renderable);
    
    if (index != v.end())
        v.erase(index);
}
