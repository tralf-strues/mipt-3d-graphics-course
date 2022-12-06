#version 330

in vec4 frag_color;
in vec3 frag_model_pos;

out vec4 outColor;

void main() {
    outColor = vec4(frag_color.xyz * clamp(1.5 - length(frag_model_pos), 0.05, 1), 1);
}