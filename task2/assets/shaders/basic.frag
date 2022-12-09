#version 330

in vec4 frag_color;
in vec2 frag_uv;

out vec4 outColor;

uniform sampler2D albedo;

void main() {
    outColor = frag_color * texture(albedo, frag_uv);
}