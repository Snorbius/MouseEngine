#version 410 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_transform;
  
out vec4 vertexColor;

void main()
{
    gl_Position = u_transform * vec4(aPos, 1.0);
    
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}