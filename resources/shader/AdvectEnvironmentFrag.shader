#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

const uint VIRTUAL_GRID_WIDTH = 128;
const uint VIRTUAL_GRID_HEIGHT = 128;

const uint ACTUAL_GRID_WIDTH = VIRTUAL_GRID_WIDTH+2;
const uint ACTUAL_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+2;

const uint U_STAGGERED_GRID_WIDTH = VIRTUAL_GRID_WIDTH+1;
const uint U_STAGGERED_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+2;

const uint V_STAGGERED_GRID_WIDTH = VIRTUAL_GRID_WIDTH+2;
const uint V_STAGGERED_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+1;

layout(location = 0) in vec2 fTexCoord;
layout(location = 1) in vec2 fVelocity;
layout(location = 2) in vec2 fPrevVelocity;

layout(std430, binding = 0) buffer UQuantity {
    float u[];
};

layout(std430, binding = 1) buffer VQuantity {
    float v[];
};

layout(location = 0) out vec4 fColor;

uniform float dt0;
uniform sampler2D samplerWeed;

vec4 linearInterpolate2D(vec2 portion, vec4 ll, vec4 lr, vec4 ul, vec4 ur) {
    return (1 - portion.y) * ((1 - portion.x) * ll + portion.x * lr) + portion.y * ((1 - portion.x) * ul + portion.x * ur);
}

void main() {
    vec2 before_advect_xy = fTexCoord - dt0 * 0.5 * vec2(fVelocity.x + fPrevVelocity.x, fVelocity.y + fPrevVelocity.y);
    vec2 lower_bound = vec2(0.5);
    vec2 upper_bound = vec2(VIRTUAL_GRID_WIDTH);
    upper_bound += vec2(0.5);
    before_advect_xy = clamp(before_advect_xy, lower_bound, upper_bound);

    // Transform
//    uvec2 lower_left_xy = uvec2(before_advect_xy * scalar);
//    uvec2 upper_right_xy = lower_left_xy+uvec2(1);

    // Linear interpolate
    //    vec4 ll = texelFetch(samplerWeed, ivec2(lower_left_xy), 0);
    //    vec4 lr = texelFetch(samplerWeed, ivec2(upper_right_xy.x, lower_left_xy.y), 0);
    //    vec4 ul = texelFetch(samplerWeed, ivec2(lower_left_xy.x, upper_right_xy.y), 0);
    //    vec4 ur = texelFetch(samplerWeed, ivec2(upper_right_xy), 0);
    //    fColor = linearInterpolate2D(vec2(fract(before_advect_xy.x - int(before_advect_xy.x)), fract(before_advect_xy.y - int(before_advect_xy.y))), ll, lr, ul, ur);
    //    fColor = texture(samplerWeed, before_advect_xy/vec2(VIRTUAL_GRID_HEIGHT, VIRTUAL_GRID_WIDTH));
    vec4 ll = texture(samplerWeed, ivec2(lower_left_xy), 0);
    vec4 lr = texture(samplerWeed, ivec2(upper_right_xy.x, lower_left_xy.y), 0);
    vec4 ul = texture(samplerWeed, ivec2(lower_left_xy.x, upper_right_xy.y), 0);
    vec4 ur = texture(samplerWeed, ivec2(upper_right_xy), 0);
    vec2 sampleCoord = linearInterpolate2D(vec2(fract(before_advect_xy.x - int(before_advect_xy.x)), fract(before_advect_xy.y - int(before_advect_xy.y))),
        vec2(lower_left_xy),
        vec2(upper_right_xy.x, lower_left_xy.y),
        vec2(lower_left_xy.x, upper_right_xy.y),
        vec2(upper_right_xy)
    );
    fColor = texture(samplerWeed, sampleCoord/vec2(VIRTUAL_GRID_HEIGHT, VIRTUAL_GRID_WIDTH), 0);
}
