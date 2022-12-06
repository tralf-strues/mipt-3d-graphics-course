#version 330

in vec4 frag_color;
out vec4 outColor;

uniform sampler2D color_texture;
// uniform sampler2D depth_texture;

void main()
{
    vec2 uv = vec2(gl_FragCoord.x / 1280, gl_FragCoord.y / 720);
    // vec2 uv = gl_FragCoord.xy / gl_FragCoord.w;

    vec4 dst_color = texture(color_texture, uv);
    // float dst_depth = texture(depth_texture, uv).r;

    outColor = dst_color;
}