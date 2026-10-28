#version 410 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

uniform mat3 u_transform;
  
out vec4 vertexColor; // specify a color output to the fragment shader

void main()
{
    float rot_angle = u_transform[2][0];
    
    vec3 final_pos = aPos;
    final_pos *= u_transform[1]; // scale;
    float x = final_pos.x;
    float y = final_pos.y;
    final_pos.x = x * cos(rot_angle) - y * sin(rot_angle);
    final_pos.y = y * cos(rot_angle) + x * sin(rot_angle);
    gl_Position = vec4((final_pos + u_transform[0]), 1.0); // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}