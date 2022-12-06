#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

out vec4 frag_color;
out vec3 frag_model_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float time;

void main()
{
    vec3 radius_pos = normalize(inPosition);
    float alpha = abs(sin(0.75 * time));

    frag_model_pos = (1 - alpha) * 1.5 * inPosition + alpha * 0.5 * radius_pos;

    gl_Position = proj * view * model * vec4(frag_model_pos, 1);
    frag_color  = inColor;
}