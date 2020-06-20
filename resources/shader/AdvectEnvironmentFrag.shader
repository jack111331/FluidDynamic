#version 450 core

layout(location = 0) in vec2 fTexCoord;

layout(location = 0) out vec4 fColor;

uniform float dt;
uniform float gridSize;
uniform sampler2D samplerWeed;
uniform sampler2D samplerVelocity;

vec4 getGridVelocity(vec2 texCoord) {
    return texture(samplerVelocity, texCoord);
}

void main() {
    vec2 before_advect_xy = fTexCoord - dt * 0.5 * vec2(getGridVelocity(fTexCoord));
    vec2 lower_bound = vec2(0.0);
    vec2 upper_bound = vec2(1.0);
    before_advect_xy = clamp(before_advect_xy, lower_bound, upper_bound);

    fColor = texture(samplerWeed, before_advect_xy);
//    fColor = vec4(vec2(getGridVelocity(fTexCoord)), 0.0, 1.0);
}
