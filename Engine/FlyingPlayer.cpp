#include "FlyingPlayer.h"

#include "AssetManager.h"
#include "BaseCamera.h"
#include "InputManager.h"
#include "MouseEngineContext.h"
#include "Resources/Material.h"

FlyingPlayer::FlyingPlayer()
{
    playerMesh.mesh = EngineContext->Assets->LoadMesh("Engine/Content/Meshes/sphere.obj");
    playerMesh.SetMaterial(Material::LoadResource<Material>("Engine/Content/Materials/MouseMaterial.material"));
}

void FlyingPlayer::HandleMovement(float deltaTime)
{
    // Pretty ugly but ehh
    int forwardKey = inputMode == WASD ? GLFW_KEY_W : GLFW_KEY_UP;
    int backwardKey = inputMode == WASD ? GLFW_KEY_S : GLFW_KEY_DOWN;
    int rightKey = inputMode == WASD ? GLFW_KEY_D : GLFW_KEY_RIGHT;
    int leftKey = inputMode == WASD ? GLFW_KEY_A : GLFW_KEY_LEFT;
    int upKey = inputMode == WASD ? GLFW_KEY_SPACE : GLFW_KEY_KP_0;
    int downKey = inputMode == WASD ? GLFW_KEY_LEFT_CONTROL : GLFW_KEY_RIGHT_CONTROL;
    
    glm::vec3 move = glm::vec3(0.0f);
    if (EngineContext->Input->IsKeyPressedDown(forwardKey))
        move.z += 1.0f;
    if (EngineContext->Input->IsKeyPressedDown(backwardKey))
        move.z -= 1.0f;
    if (EngineContext->Input->IsKeyPressedDown(rightKey))
        move.x += 1.0f;
    if (EngineContext->Input->IsKeyPressedDown(leftKey))
        move.x -= 1.0f;
    if (EngineContext->Input->IsKeyPressedDown(upKey))
        move.y += 1.0f;
    if (EngineContext->Input->IsKeyPressedDown(downKey))
        move.y -= 1.0f;

    if (glm::length(move) < 0.01)
        return;

    const float speed = 10.0f;

    glm::vec3 moveVector = glm::vec3(0.0f);
    
    Transform* axisTransform = playerCamera == nullptr ? &transform : &playerCamera->transform;
    
    moveVector += move.x * axisTransform->GetRight();
    moveVector += move.y * axisTransform->GetUp();
    moveVector += move.z * axisTransform->GetForward();

    moveVector = glm::normalize(moveVector);

    transform.Translate(moveVector * speed * deltaTime);
}

void FlyingPlayer::Process(float deltaTime)
{
    HandleMovement(deltaTime);
    playerMesh.transform = transform;
}

void FlyingPlayer::SetInputMode(PlayerInputMode mode)
{
    inputMode = mode;
}
