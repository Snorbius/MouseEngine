#include "Transform.h"

Transform::Transform()
{
    UpdateData();
}

void Transform::UpdateData()
{
    data[0] = position.x;
    data[1] = position.y;
    data[2] = position.z;
    
    data[3] = scale.x;
    data[4] = scale.y;
    data[5] = scale.z;
    
    data[6] = rotation.x;
    data[7] = rotation.y;
    data[8] = rotation.z;
}

void Transform::SetPosition(glm::vec3 value)
{
    position = value;
    UpdateData();
}

void Transform::SetScale(glm::vec3 value)
{
    scale = value;
    UpdateData();
}

void Transform::SetRotation(glm::vec3 value)
{
    rotation = value;
    UpdateData();
}
