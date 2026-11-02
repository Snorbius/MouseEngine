#version 410 core
out vec4 FragColor;

uniform vec4 u_color;
  
in vec4 vertexColor;

void main()
{
    // FragColor = u_color;
    FragColor = vertexColor;
    //FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
} 