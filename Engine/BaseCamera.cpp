#include "BaseCamera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "MouseEngineContext.h"

BaseCamera::BaseCamera()
{
    MouseEngineContext::GetInstance()->RegisterForInput(this);
}

glm::mat4 BaseCamera::GetView() const
{
    // glm::vec3 rotation = transform.GetRotation();
    // glm::vec3 direction;
    // direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    // direction.y = sin(glm::radians(rotation.x));
    // direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    
    glm::vec3 pos2 = transform.GetPosition();
    return glm::lookAt(pos2, pos2 + transform.GetForward(), glm::vec3(0, 1, 0));
}

glm::mat4 BaseCamera::GetProjection() const
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void BaseCamera::SetAspectRatio(float ratio)
{
    aspectRatio = ratio;
}

bool BaseCamera::InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_A:
            transform.Translate(transform.GetRight() * 0.1f);
            break;
        case GLFW_KEY_D:
            transform.Translate(-transform.GetRight() * 0.1f);
            break;
        case GLFW_KEY_W:
            transform.Translate(transform.GetForward() * 0.1f);
            break;
        case GLFW_KEY_S:
            transform.Translate(-transform.GetForward() * 0.1f);
            break;
        case GLFW_KEY_SPACE: 
            transform.Translate(transform.GetUp() * 0.1f);
            break;
        case GLFW_KEY_LEFT_CONTROL:
            transform.Translate(-transform.GetUp() * 0.1f);
            break;
        default: ;
        }
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        print_line("YAHOO :D");
    
    return false;
}

void BaseCamera::Process(float deltaTime)
{
    transform.Rotate(glm::vec3(0, 2, 0));
}
