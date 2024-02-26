#version 330 core

in vec2 tex_coord;
out vec4 o_color;

uniform sampler2D tex0;

void main() {
    o_color = texture(tex0, tex_coord);
}
