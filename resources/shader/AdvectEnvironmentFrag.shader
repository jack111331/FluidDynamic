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

layout(std430, binding = 0) buffer UQuantity {
    float u[];
};

layout(std430, binding = 1) buffer VQuantity {
    float v[];
};

layout(location = 0) out vec4 fColor;

uniform float dt0;
uniform sampler2D samplerWeed;

uint indexOfVelocityU(uvec2 grid_xy) {
    return grid_xy.y * U_STAGGERED_GRID_WIDTH + grid_xy.x;
}

uint indexOfVelocityV(uvec2 grid_xy) {
    return grid_xy.y * V_STAGGERED_GRID_WIDTH + grid_xy.x;
}
vec4 linearInterpolate2D(vec2 portion, vec4 ll, vec4 lr, vec4 ul, vec4 ur) {
    return (1 - portion.y) * ((1 - portion.x) * ll + portion.x * lr) + portion.y * ((1 - portion.x) * ul + portion.x * ur);
}

vec2 linearInterpolate2D(vec2 portion, vec2 ll, vec2 lr, vec2 ul, vec2 ur) {
    return (1 - portion.y) * ((1 - portion.x) * ll + portion.x * lr) + portion.y * ((1 - portion.x) * ul + portion.x * ur);
}

void main() {
    // Scalar
    // TODO accurate_xy
    ivec2 textureSize = textureSize(samplerWeed, 0);
    vec2 scalar = vec2(textureSize) / vec2(VIRTUAL_GRID_HEIGHT, VIRTUAL_GRID_WIDTH);
    uvec2 accurate_xy = uvec2(fTexCoord*vec2(VIRTUAL_GRID_HEIGHT, VIRTUAL_GRID_WIDTH)+vec2(1));
    vec2 before_advect_xy = accurate_xy - dt0 * 0.5
    * vec2((u[indexOfVelocityU(accurate_xy)] + u[indexOfVelocityU(uvec2(accurate_xy.x-1, accurate_xy.y))])
    , v[indexOfVelocityV(accurate_xy)] + v[indexOfVelocityV(uvec2(accurate_xy.x, accurate_xy.y-1))]);
    vec2 lower_bound = vec2(0.5);
    vec2 upper_bound = vec2(VIRTUAL_GRID_WIDTH);
    upper_bound += vec2(0.5);
    before_advect_xy = clamp(before_advect_xy, lower_bound, upper_bound);

    // Transform
    uvec2 lower_left_xy = uvec2(before_advect_xy * scalar);
    uvec2 upper_right_xy = lower_left_xy+uvec2(1);

    // Linear interpolate
    vec4 ll = texelFetch(samplerWeed, ivec2(lower_left_xy), 0);
    vec4 lr = texelFetch(samplerWeed, ivec2(upper_right_xy.x, lower_left_xy.y), 0);
    vec4 ul = texelFetch(samplerWeed, ivec2(lower_left_xy.x, upper_right_xy.y), 0);
    vec4 ur = texelFetch(samplerWeed, ivec2(upper_right_xy), 0);
    fColor = linearInterpolate2D(vec2(fract(before_advect_xy.x - int(before_advect_xy.x)), fract(before_advect_xy.y - int(before_advect_xy.y))), ll, lr, ul, ur);
//    fColor = texture(samplerWeed, before_advect_xy/vec2(VIRTUAL_GRID_HEIGHT, VIRTUAL_GRID_WIDTH));
//    vec2 sampleCoord = linearInterpolate2D(vec2(fract(before_advect_xy.x - int(before_advect_xy.x)), fract(before_advect_xy.y - int(before_advect_xy.y))),
//    vec2(lower_left_xy),
//    vec2(upper_right_xy.x, lower_left_xy.y),
//    vec2(lower_left_xy.x, upper_right_xy.y),
//    vec2(upper_right_xy)
//    );
//    fColor = texture(samplerWeed, sampleCoord/vec2(VIRTUAL_GRID_HEIGHT, VIRTUAL_GRID_WIDTH), 0);
}
