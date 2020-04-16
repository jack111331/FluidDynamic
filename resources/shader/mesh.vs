#version 450 core
 
layout (location = 0) in vec3 pos;
layout (location = 1) in float inColor;
out vec4 color;

void main()
{
    gl_Position = vec4(pos, 1.0);
    float fixedColor = inColor;
    if(fixedColor >= 1.0) {
        fixedColor = 1.0;
    }
    color = vec4(fixedColor, fixedColor, fixedColor, 1.0);
}
