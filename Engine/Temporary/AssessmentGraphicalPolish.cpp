#include "AssessmentGraphicalPolish.h"

#include "../AssetManager.h"
#include "../MouseEngineContext.h"
#include "../Texture.h"
#include "../TimeManager.h"

AssessmentGraphicalPolish::AssessmentGraphicalPolish()
{
    cirnoTexture = EngineContext->Assets->LoadTexture("Engine/Content/Textures/Cirno_256.png");
    cirno.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/cirno.obj");
    cirno.transform.SetPosition({0, -2, 0});
    cirno.transform.SetScale({3, 3, 3});
}

void AssessmentGraphicalPolish::Render(Shader* shader)
{
    shader->SetUniform("u_texture_color_alpha", 0.0f);
    cirnoTexture->Use();
    cirno.Render(shader);
}

void AssessmentGraphicalPolish::Process(float deltaTime)
{
    float time = EngineContext->Time->GetTotalElapsedTimef();
    
    cirno.transform.Rotate(glm::vec3(0, 1, 0) * deltaTime * 145.0f);
    glm::vec3 s = cirno.transform.GetScale();
    cirno.transform.SetScale({s.x, s.y + sin(time * 12.5f) * 0.025 * s.y, s.z});
}
