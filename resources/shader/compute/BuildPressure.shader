#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

#define VIRTUAL_GRID_WIDTH 256
#define VIRTUAL_GRID_HEIGHT 256

#define ACTUAL_GRID_WIDTH VIRTUAL_GRID_WIDTH+2
#define ACTUAL_GRID_HEIGHT VIRTUAL_GRID_HEIGHT+2

// one thread each work group

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer Pressure {
    float pressure[];
};

layout(std430, binding = 1) buffer PrevPressure {
    float prevPressure[];
};

layout(std430, binding = 2) buffer UQuantity {
    float u[];
};

layout(std430, binding = 3) buffer VQuantity {
    float v[];
};

uniform float inv;

uint indexOfVelocityU(uvec2 grid_xy);
uint indexOfVelocityV(uvec2 grid_xy);

void main() {
    // Invoke workgroup (N, N, 1)
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x+1, gl_WorkGroupID.y+1);
    prevPressure[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x] = -(u[indexOfVelocityU(uvec2(accurate_workgroup_xy.x, accurate_workgroup_xy.y))] - u[indexOfVelocityU(uvec2(accurate_workgroup_xy.x-1, accurate_workgroup_xy.y))]
    + v[indexOfVelocityV(uvec2(accurate_workgroup_xy.x, accurate_workgroup_xy.y))] - v[indexOfVelocityU(uvec2(accurate_workgroup_xy.x, accurate_workgroup_xy.y-1))]
    ) / VIRTUAL_GRID_WIDTH;
    pressure[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x] = 0.0;
}
