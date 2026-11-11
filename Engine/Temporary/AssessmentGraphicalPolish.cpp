#include "AssessmentGraphicalPolish.h"

#include "../AssetManager.h"
#include "../MouseEngineContext.h"
#include "../Resources/Material.h"
#include "../TimeManager.h"
#include "../Resources/Resource.h"

AssessmentGraphicalPolish::AssessmentGraphicalPolish()
{
    cirnoMaterial = Resource::LoadResource<Material>(R"(Engine/Content/Materials/Basic.cheese)");
    cirno.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/cirno.obj");
    cirno.transform.SetPosition({0, -2, 0});
    cirno.transform.SetScale({3, 3, 3});
}

void AssessmentGraphicalPolish::Render(Shader* shader)
{
    if (cirnoMaterial != nullptr)
    {
        cirnoMaterial->shader->SetUniform("u_texture_color_alpha", 0.0f);
        cirnoMaterial->Use();
    }
    cirno.Render(cirnoMaterial != nullptr ? cirnoMaterial->shader : shader);
}

void AssessmentGraphicalPolish::Process(float deltaTime)
{
    float time = EngineContext->Time->GetTotalElapsedTimef();
    
    cirno.transform.Rotate(glm::vec3(0, 1, 0) * deltaTime * 145.0f);
    glm::vec3 s = cirno.transform.GetScale();
    cirno.transform.SetScale({s.x, s.x + sin(time * 12.5f) * 0.15 * s.x, s.z});
}
