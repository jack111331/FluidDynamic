#version 450 core

layout (location = 0) in vec4 pos;
layout (location = 2) in vec4 col;

out vec4 color;
void main()
{
    gl_Position = vec4(pos.xyz, pos.w);
    color = col;
}
