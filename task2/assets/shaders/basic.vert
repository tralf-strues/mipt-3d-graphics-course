#version 330

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec4 aColor;
layout(location = 3) in vec2 aUV;

out vec4 frag_color;
out vec2 frag_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float time;

void main()
{
    gl_Position = proj * view * model * vec4(aPosition, 1);
    frag_color  = aColor;
    frag_uv     = aUV;
}