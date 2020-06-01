#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

#define VIRTUAL_GRID_WIDTH 256
#define VIRTUAL_GRID_HEIGHT 256

#define ACTUAL_GRID_WIDTH VIRTUAL_GRID_WIDTH+2
#define ACTUAL_GRID_HEIGHT VIRTUAL_GRID_HEIGHT+2

layout(local_size_x = ACTUAL_GRID_WIDTH, local_size_y = 1) in;

layout(std430, binding = 0) buffer Density {
    float density[];
};

void main() {
    uvec2 accurate_workgroup_xy = uvec2(gl_LocalInvocationID.x+1, gl_LocalInvocationID.y+1);
    // (1, 0) ~ (N, 0)
    density[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH] = density[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + 1];
    // (1, N+1) ~ (N, N+1)
    density[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + (VIRTUAL_GRID_WIDTH + 1)] = density[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + (VIRTUAL_GRID_WIDTH + 1) - 1];
    // (0, 1) ~ (0, N)
    density[accurate_workgroup_xy.x] = density[accurate_workgroup_xy.x + ACTUAL_GRID_WIDTH];
    // (N+1, 1) ~ (N+1, N)
    density[(VIRTUAL_GRID_HEIGHT+1) * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x] = density[VIRTUAL_GRID_HEIGHT * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x];

    // TODO Memory Barrier
    // All density will synchronize here
    barrier();
    // (0, 0)
    density[0] = 0.5 * (density[1] + density[ACTUAL_GRID_WIDTH]);
    // (N+1, 0)
    density[(VIRTUAL_GRID_HEIGHT+1) * ACTUAL_GRID_WIDTH] = 0.5 * (density[VIRTUAL_GRID_HEIGHT * ACTUAL_GRID_WIDTH] + density[(VIRTUAL_GRID_HEIGHT+1) * ACTUAL_GRID_WIDTH + 1]);
    // (0, N+1)
    density[(VIRTUAL_GRID_WIDTH+1)] = 0.5 * (density[(VIRTUAL_GRID_WIDTH+1) + ACTUAL_GRID_WIDTH] + density[VIRTUAL_GRID_HEIGHT]);
    // (N+1, N+1)
    density[(VIRTUAL_GRID_HEIGHT+1) * ACTUAL_GRID_WIDTH + (VIRTUAL_GRID_WIDTH+1)] = 0.5 * (density[(VIRTUAL_GRID_HEIGHT+1) * ACTUAL_GRID_WIDTH + VIRTUAL_GRID_WIDTH] + density[VIRTUAL_GRID_HEIGHT * ACTUAL_GRID_WIDTH + (VIRTUAL_GRID_WIDTH+1)]);
}
