#version 410 core
out vec4 FragColor;

uniform vec4 u_color;

uniform sampler2D texture1;
  
in vec4 vertexColor;
in vec2 vertexUv;

void main()
{
    //FragColor = vertexColor;
    FragColor = texture(texture1, vertexUv) * vertexColor;
} 