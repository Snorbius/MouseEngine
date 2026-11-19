#include "AssessmentGraphicalPolish.h"

#include "../AssetManager.h"
#include "../MouseEngineContext.h"
#include "../Resources/Material.h"
#include "../TimeManager.h"
#include "../Resources/Resource.h"

AssessmentGraphicalPolish::AssessmentGraphicalPolish()
{
    shadedCirno.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/cirno.obj");
    shadedCirno.SetMaterial(Resource::LoadResource<Material>(R"(Engine/Content/Materials/Basic.material)"));
    
    unlitCirno.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/cirno.obj");
    unlitCirno.SetMaterial(Material::GetFallbackMaterial());
    
    monkey.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/monkey.obj");
    monkey.SetMaterial(Resource::LoadResource<Material>(R"(Engine/Content/Materials/Basic.material)"));
    
    icoSphere.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/sphere.obj");
    icoSphere.SetMaterial(Resource::LoadResource<Material>(R"(Engine/Content/Materials/Basic.material)"));
    
    mouse.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/mouse.obj");
    mouse.SetMaterial(Resource::LoadResource<Material>(R"(Engine/Content/Materials/MouseMaterial.material)"));
    
    hotdog.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/homtdog.obj");
    hotdog.SetMaterial(Resource::LoadResource<Material>(R"(Engine/Content/Materials/Basic.material)"));
    
    safi.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/mouse.obj");
    safi.SetMaterial(Resource::LoadResource<Material>(R"(Engine/Content/Materials/SafiMaterial.material)"));
    
    shadedCirno.transform.SetPosition({3, -2, 0});
    shadedCirno.transform.SetScale(2);
    
    unlitCirno.transform.SetPosition({-3, -2, 0});
    unlitCirno.transform.SetScale(2);
    
    monkey.transform.SetPosition({0, 1, 0});
    
    icoSphere.transform.SetPosition({0, -2, 0});
    
    mouse.transform.SetPosition({-3, 3, 0});
    mouse.transform.SetScale(4);
    
    hotdog.transform.SetPosition({0, 4, 0});
    hotdog.transform.SetScale(3);
    
    safi.transform.SetPosition({0, 0, -15});
    safi.transform.SetScale(8);
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
    
    icoSphere.transform.SetScale(1 + sin(time * 0.5f) * 0.2f);
    icoSphere.transform.Rotate(glm::vec3(sin(time * 0.34), cos(time * 0.86f), sin(time * 0.12f) * deltaTime));
    
    float distanceFromCenter = 5.0f;
    float scaledTime = time * 3.5f;
    glm::vec3 mousePos = glm::vec3(sin(scaledTime), sin(scaledTime * 0.4f) * 0.5f, cos(scaledTime)) * distanceFromCenter;
    glm::vec3 mousePos2 = glm::vec3(sin(scaledTime + 0.0001f), sin(scaledTime * 0.4f) * 0.5f, cos(scaledTime + 0.0001f)) * distanceFromCenter;
    mouse.transform.SetPosition(mousePos);
    
    glm::vec3 rot = glm::normalize(mousePos2 - mousePos);
    mouse.transform.PointAt(mousePos2);
    
    hotdog.transform.Rotate(glm::vec3(0, 1, 0) * deltaTime * 30.0f);
}
