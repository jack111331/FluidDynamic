#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

#define VIRTUAL_GRID_WIDTH 256
#define VIRTUAL_GRID_HEIGHT 256

#define U_STAGGERED_GRID_WIDTH VIRTUAL_GRID_WIDTH+1
#define U_STAGGERED_GRID_HEIGHT VIRTUAL_GRID_HEIGHT+2

#define V_STAGGERED_GRID_WIDTH VIRTUAL_GRID_WIDTH+2
#define V_STAGGERED_GRID_HEIGHT VIRTUAL_GRID_HEIGHT+1

// one thread each work group

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer VQuantity {
    float v[];
};
layout(std430, binding = 1) buffer UPrevQuantity {
    float prevU[];
};
layout(std430, binding = 2) buffer VPrevQuantity {
    float prevV[];
};

uint indexOfVelocityU(uvec2 grid_xy);
uint indexOfVelocityV(uvec2 grid_xy);
float linearInterpolate2D(vec2 portion, float ll, float lr, float ul, float ur);

uniform float dt0;

void main() {
    // Invoke workgroup (N, N-1, 1)
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x+1, gl_WorkGroupID.y+1);
    const uint grid_xy = accurate_workgroup_xy.y * V_STAGGERED_GRID_WIDTH + accurate_workgroup_xy.x;
    vec2 before_advect_xy = vec2(
        accurate_workgroup_xy.x - dt0 * 0.25 * (prevU[indexOfVelocityU(uvec2(accurate_workgroup_xy.x-1, accurate_workgroup_xy.y))]
        + prevU[indexOfVelocityU(uvec2(accurate_workgroup_xy))]
        + prevU[indexOfVelocityU(uvec2(accurate_workgroup_xy.x-1, accurate_workgroup_xy.y+1))]
        + prevU[indexOfVelocityU(uvec2(accurate_workgroup_xy.x, accurate_workgroup_xy.y+1))],
        accurate_workgroup_xy.y  - dt0 * prevV[indexOfVelocityV(accurate_workgroup_xy)]
    ));
    before_advect_xy = clamp(before_advect_xy, vec2(0.5, 0.0), vec2(VIRTUAL_GRID_WIDTH+0.5, VIRTUAL_GRID_WIDTH));
    uvec2 lower_left_xy = uvec2(before_advect_xy);
    uvec2 upper_right_xy = lower_left_xy+uvec2(1);
    // Linear interpolate
    v[grid_xy] = linearInterpolate2D(vec2(fract(before_advect_xy.x - lower_left_xy.x), fract(before_advect_xy.y - lower_left_xy.y)),
    prevV[indexOfVelocityV(lower_left_xy)],
    prevV[indexOfVelocityV(uvec2(upper_right_xy.x, lower_left_xy.y))],
    prevV[indexOfVelocityV(uvec2(lower_left_xy.x, upper_right_xy.y))],
    prevV[indexOfVelocityU(upper_right_xy)]);
}
