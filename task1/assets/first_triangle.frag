#version 330

in vec4 frag_color;

out vec4 outColor;
// out float outDepth;

void main() {
    outColor = frag_color;
    // outDepth = gl_FragDepth;
}