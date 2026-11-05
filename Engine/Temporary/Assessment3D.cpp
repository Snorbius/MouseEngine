#include "Assessment3D.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "../MouseEngineContext.h"
#include "../TimeManager.h"

Assessment3D::Assessment3D()
{
    cube.transform.SetScale(glm::vec3(0.5f));
    sphere.transform.SetScale(glm::vec3(0.75f));
}

void Assessment3D::Render(Shader* shader)
{
    float time = EngineContext->Time->GetTotalElapsedTimef();
    float offset = ((sin(time) + 1) / 2) * 2.0f;
    pyramid.transform.SetScale(glm::vec3(1 + pow(offset * 0.5f, 2.0f)));
    glm::vec3 pScale = pyramid.transform.GetScale();
    pyramid.transform.SetScale(pScale);
    pyramid.Render(shader);
    pyramid.transform.SetScale({pScale.x, pScale.y * -1, pScale.z});
    glFrontFace(GL_CW);
    pyramid.Render(shader);
    glFrontFace(GL_CCW);

    
    const glm::vec3 cubeOffsets[] = {
        {-1, -1, -1},
        {-1, -1, 1},
        {-1, 1, 1},
        {1, 1, 1},
        {1, 1, -1},
        {1, -1, -1},
        {-1, 1, -1},
        {1, -1, 1},
    };
    for (int i = 0; i < 8; ++i)
    {
        cube.transform.SetPosition(cubeOffsets[i] + cubeOffsets[i] * offset);
        cube.Render(shader);
    }
    
    const int numSpheres = 16;

    for (int i = 0; i < numSpheres; ++i)
    {
        float angle = glm::radians((360.0f / numSpheres) * static_cast<float>(i) + time * 30.0f);
        float x = sin(angle);
        float y = cos(angle);
        sphere.transform.SetPosition(glm::vec3(x, 0, y) * (offset + 3.0f));
        sphere.Render(shader);
    }
}

void Assessment3D::Process(float deltaTime)
{
    cube.transform.Rotate(glm::vec3(0, 45, 0) * deltaTime);
    pyramid.transform.Rotate(glm::vec3(0, -45, 0) * deltaTime);
}
