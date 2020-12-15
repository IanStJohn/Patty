#version 430

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uvs;

uniform float time;
uniform mat4 MVP;
uniform vec4 v_rgba;

out float f_time;
out vec2 f_uvs;
out vec4 f_rgba;

void main() {
    gl_Position = MVP * vec4(pos, 1);
    f_time = time;
    f_uvs = uvs;
    f_rgba = v_rgba;
}