#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

const uint VIRTUAL_GRID_WIDTH = 128;
const uint VIRTUAL_GRID_HEIGHT = 128;

const uint ACTUAL_GRID_WIDTH = VIRTUAL_GRID_WIDTH+2;
const uint ACTUAL_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+2;

// one thread each work group

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer Density {
    float density[];
};

layout(std430, binding = 1) buffer PrevDensity {
    float prevDensity[];
};

layout(std430, binding = 2) buffer UQuantity {
    float u[];
};

layout(std430, binding = 3) buffer VQuantity {
    float v[];
};

uniform float dt0;

uint indexOfVelocityU(uvec2 grid_xy);
uint indexOfVelocityV(uvec2 grid_xy);
float linearInterpolate2D(vec2 portion, float ll, float lr, float ul, float ur);

void main() {
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x+1, gl_WorkGroupID.y+1);
    const uint grid_xy = accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x;
    vec2 before_advect_xy = accurate_workgroup_xy - dt0 * 0.5
    * vec2((u[indexOfVelocityU(accurate_workgroup_xy)] + u[indexOfVelocityU(uvec2(accurate_workgroup_xy.x-1, accurate_workgroup_xy.y))])
    , v[indexOfVelocityV(accurate_workgroup_xy)] + v[indexOfVelocityV(uvec2(accurate_workgroup_xy.x, accurate_workgroup_xy.y-1))]);
    before_advect_xy = clamp(before_advect_xy, vec2(0.5), vec2(VIRTUAL_GRID_WIDTH+0.5));
    uvec2 lower_left_xy = uvec2(before_advect_xy);
    uvec2 upper_right_xy = lower_left_xy+uvec2(1);
    // Linear interpolate
    density[grid_xy] = linearInterpolate2D(vec2(fract(before_advect_xy.x - lower_left_xy.x), fract(before_advect_xy.y - lower_left_xy.y)),
    prevDensity[lower_left_xy.y * ACTUAL_GRID_WIDTH + lower_left_xy.x],
    prevDensity[lower_left_xy.y * ACTUAL_GRID_WIDTH + upper_right_xy.x],
    prevDensity[upper_right_xy.y * ACTUAL_GRID_WIDTH + lower_left_xy.x],
    prevDensity[upper_right_xy.y * ACTUAL_GRID_WIDTH + upper_right_xy.x]);

}
