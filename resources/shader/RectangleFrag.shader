#version 450 core

layout(location = 0) in vec2 fTexCoord;

layout(location = 0) out vec4 fColor;

uniform sampler2D samplerWeed;

void main() {
    fColor = texture(samplerWeed, fTexCoord);
}
