#version 450 core

layout(location = 0) in vec3 vCoord;
layout(location = 2) in vec2 vTexCoord;

layout(location = 0) out vec2 fTexCoord;

void main() {
    gl_Position = vec4(vCoord, 1.0);
    fTexCoord = vTexCoord;
}
