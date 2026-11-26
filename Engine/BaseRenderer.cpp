#include "BaseRenderer.h"

#include "BaseCamera.h"
#include "BaseMesh.h"
#include "Renderable.h"
#include "ECS/ComponentManager.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/NewMeshComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "Resources/Material.h"

BaseRenderer::BaseRenderer()
{
    EngineContext = MouseEngineContext::GetInstance();
}

void BaseRenderer::ClearScreen()
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void BaseRenderer::RenderScreen(const glm::mat4& view, const glm::mat4& projection)
{
    ClearScreen();
    
    for (Shader* element : EngineContext->Assets->GetAllLoadedShaders())
    {
        element->SetUniform("u_view", view);
        element->SetUniform("u_projection", projection);
    }
    
    RenderComponents(view, projection);
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
    
    renderableMaterialMap.erase(renderable);
}

void BaseRenderer::SetClearColor(glm::vec4 color)
{
    clearColor = color;
}

void BaseRenderer::SetViewportDimensions(int x, int y, int width, int height)
{
    viewport.x = x;
    viewport.y = y;
    viewport.z = width;
    viewport.w = height;
    
    glViewport(x, y, width, height);
    glScissor(x, y, width, height);
}

void BaseRenderer::ClearEntireScreen()
{
    glDisable(GL_SCISSOR_TEST);
    ClearScreen();
    glEnable(GL_SCISSOR_TEST);
}

void BaseRenderer::RenderComponents(const glm::mat4& view, const glm::mat4& projection)
{
    std::vector<Entity> entities = EngineContext->Components->FilterEntities<NewMeshComponent, TransformComponent>(EngineContext->Entities->GetAllEntities());

    for (Entity entity : entities)
    {
        TransformComponent& transform = EngineContext->Components->GetComponent<TransformComponent>(entity);
        NewMeshComponent& mesh = EngineContext->Components->GetComponent<NewMeshComponent>(entity);
        Material* material = mesh.material;
        
        material->Use();
        material->shader->SetUniform("u_view", view);
        material->shader->SetUniform("u_projection", projection);
        
        material->shader->SetUniform("u_transform", transform.GetTransformMatrix());
        if (mesh.mesh != nullptr)
            mesh.mesh->Render(material->shader);
    }
}
