#version 410 core
out vec4 FragColor;

uniform vec4 u_color = vec4(0.98, 0.98, 0.98, 1.0);

uniform float ambientStrength = 0.20f;
uniform vec3 sunDirection = vec3(0.7071067811865476, 0.7071067811865476, 0.0);

in vec3 vertexNormal;

void main()
{
    float sunStrength = max(dot(vertexNormal, sunDirection), 0.0);
    FragColor = max(sunStrength, ambientStrength) * u_color;
} 