#include "AssessmentGraphicalPolish.h"

#include "../AssetManager.h"
#include "../MouseEngineContext.h"
#include "../TimeManager.h"

AssessmentGraphicalPolish::AssessmentGraphicalPolish()
{
    cirno.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/cirno.obj");
    cirno.transform.SetPosition({0, 3, 0});
}

void AssessmentGraphicalPolish::Render(Shader* shader)
{
    cirno.Render(shader);
}

void AssessmentGraphicalPolish::Process(float deltaTime)
{
    float time = EngineContext->Time->GetTotalElapsedTimef();
    
    cirno.transform.Rotate(glm::vec3(0, 1, 0) * deltaTime * 145.0f);
    cirno.transform.SetScale({1, 1.0f + sin(time * 12.5f) * 0.15, 1});
}
