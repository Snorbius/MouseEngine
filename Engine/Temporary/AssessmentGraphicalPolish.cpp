#include "AssessmentGraphicalPolish.h"

#include "../AssetManager.h"
#include "../MouseEngineContext.h"
#include "../Resources/Material.h"
#include "../TimeManager.h"
#include "../Resources/Resource.h"

AssessmentGraphicalPolish::AssessmentGraphicalPolish()
{
    shadedCirnoMaterial = Resource::LoadResource<Material>(R"(Engine/Content/Materials/Basic.cheese)");
    unlitCirnoMaterial = Resource::LoadResource<Material>(R"(Engine/Content/Materials/UnlitCirno.cheese)");
    monkeyMaterial = Resource::LoadResource<Material>(R"(Engine/Content/Materials/Basic.cheese)");
    
    shadedCirno.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/cirno.obj");
    unlitCirno.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/cirno.obj");
    monkey.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/monkey.obj");
    
    shadedCirno.transform.SetPosition({3, -2, 0});
    shadedCirno.transform.SetScale(2);
    
    unlitCirno.transform.SetPosition({-3, -2, 0});
    unlitCirno.transform.SetScale(2);
}

void AssessmentGraphicalPolish::Render(Shader* shader)
{
    if (shadedCirnoMaterial != nullptr)
    {
        shadedCirnoMaterial->shader->SetUniform("u_texture_color_alpha", 0.0f);
        shadedCirnoMaterial->Use();
    }
    shadedCirno.Render(shadedCirnoMaterial != nullptr ? shadedCirnoMaterial->shader : shader);
    
    if (unlitCirnoMaterial != nullptr)
        unlitCirnoMaterial->Use();
    unlitCirno.Render(unlitCirnoMaterial != nullptr ? unlitCirnoMaterial->shader : shader);

    if (monkeyMaterial != nullptr)
        monkeyMaterial->Use();
    monkey.Render(monkeyMaterial != nullptr ? monkeyMaterial->shader : shader);
}

void AssessmentGraphicalPolish::Process(float deltaTime)
{
    float time = EngineContext->Time->GetTotalElapsedTimef();
    
    shadedCirno.transform.Rotate(glm::vec3(0, 1, 0) * deltaTime * -145.0f);
    unlitCirno.transform.Rotate(glm::vec3(0, 1, 0) * deltaTime * 145.0f);
    glm::vec3 s = shadedCirno.transform.GetScale();
    glm::vec3 newScale = glm::vec3(s.x, s.x + sin(time * 12.5f) * 0.15 * s.x, s.z);
    shadedCirno.transform.SetScale(newScale);
    unlitCirno.transform.SetScale(newScale);
}
