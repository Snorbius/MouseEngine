#version 410 core
out vec4 FragColor;

uniform vec4 u_color;
uniform float u_texture_color_alpha = 0.5;

uniform float ambientStrength = 0.20f;
uniform vec3 sunDirection = vec3(0.7071067811865476, 0.7071067811865476, 0.0);

uniform sampler2D texture1;
  
in vec4 vertexColor;
in vec2 vertexUv;
in vec3 vertexNormal;

void main()
{
    // FragColor = vertexColor;
    float sunStrength = max(dot(vertexNormal, sunDirection), 0.0);
    FragColor = max(sunStrength, ambientStrength) * mix(texture(texture1, vertexUv), vertexColor, u_texture_color_alpha);
    //FragColor = vec4(vertexNormal, 1.0f);
} 