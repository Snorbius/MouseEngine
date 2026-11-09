#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUv;
layout (location = 3) in vec3 aNormal;

uniform mat4 u_transform;
uniform mat4 u_view;
uniform mat4 u_projection;
  
out vec4 vertexColor;
out vec2 vertexUv;
out vec3 vertexNormal;

void main()
{
    gl_Position = u_projection * u_view * u_transform * vec4(aPos, 1.0);
    
    vertexColor = vec4(aColor, 1.0f);
    vertexUv = aUv;
    vertexNormal = normalize(u_transform * vec4(aNormal, 0.0)).xyz;
}