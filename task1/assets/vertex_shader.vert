#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

out vec4 frag_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position  = proj * view * model * vec4(inPosition, 1);
    frag_color   = inColor;
}