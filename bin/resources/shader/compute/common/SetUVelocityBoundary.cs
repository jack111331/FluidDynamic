#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable
// TODO refactor
#define VIRTUAL_GRID_WIDTH 256
#define VIRTUAL_GRID_HEIGHT 256

#define ACTUAL_GRID_WIDTH VIRTUAL_GRID_WIDTH+2
#define ACTUAL_GRID_HEIGHT VIRTUAL_GRID_HEIGHT+2

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer Density {
    float density[];
};

void SetDensityBoundary() {
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x+1, gl_WorkGroupID.y+1);
    // (1, 0) ~ (N, 0)
    density[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH] = density[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + 1];
    // (1, N+1) ~ (N, N+1)
    density[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + (VIRTUAL_GRID_WIDTH + 1)] = density[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + (VIRTUAL_GRID_WIDTH + 1) - 1];
    // (0, 1) ~ (0, N)
    density[accurate_workgroup_xy.x] = density[accurate_workgroup_xy.x + ACTUAL_GRID_WIDTH];
    // (N+1, 1) ~ (N+1, N)
    density[(VIRTUAL_GRID_HEIGHT+1) * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x] = density[ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x - ACTUAL_GRID_WIDTH];

    // TODO Memory Barrier
    // (0, 0)
    // (N+1, 0)
    // (0, N+1)
    // (N+1, N+1)
}
