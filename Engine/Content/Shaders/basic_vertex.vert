#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUv;

uniform mat4 u_transform;
uniform mat4 u_view;
uniform mat4 u_projection;
  
out vec4 vertexColor;
out vec2 vertexUv;

void main()
{
    gl_Position = u_projection * u_view * u_transform * vec4(aPos, 1.0);
    
    vertexColor = vec4(aColor, 1.0f);
    vertexUv = aUv;
}