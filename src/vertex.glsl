#version 330 core

layout (location = 0) in vec3 l_pos;
layout (location = 1) in vec2 l_tex;

out vec2 tex_coord;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * vec4(l_pos, 1.0f); 
    tex_coord = l_tex;
}
