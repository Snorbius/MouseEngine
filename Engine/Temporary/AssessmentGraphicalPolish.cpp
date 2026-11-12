#include "AssessmentGraphicalPolish.h"

#include "../AssetManager.h"
#include "../MouseEngineContext.h"
#include "../Resources/Material.h"
#include "../TimeManager.h"
#include "../Resources/Resource.h"

AssessmentGraphicalPolish::AssessmentGraphicalPolish()
{
    shadedCirno.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/cirno.obj");
    shadedCirno.material = Resource::LoadResource<Material>(R"(Engine/Content/Materials/Basic.cheese)");
    
    unlitCirno.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/cirno.obj");
    unlitCirno.material = Resource::LoadResource<Material>(R"(Engine/Content/Materials/UnlitCirno.cheese)");
    
    monkey.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/monkey.obj");
    monkey.material = Resource::LoadResource<Material>(R"(Engine/Content/Materials/Basic.cheese)");
    
    shadedCirno.transform.SetPosition({3, -2, 0});
    shadedCirno.transform.SetScale(2);
    
    unlitCirno.transform.SetPosition({-3, -2, 0});
    unlitCirno.transform.SetScale(2);
}

void AssessmentGraphicalPolish::Render(Shader* shader)
{
    shadedCirno.Render(shader);
    unlitCirno.Render(shader);
    monkey.Render(shader);
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
