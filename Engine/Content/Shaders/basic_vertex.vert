#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 u_transform;
  
out vec4 vertexColor;

void main()
{
    gl_Position = u_transform * vec4(aPos, 1.0);
    
    vertexColor = vec4(aColor, 1.0f);
}