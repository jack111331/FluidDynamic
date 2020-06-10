#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

const uint VIRTUAL_GRID_WIDTH = 128;
const uint VIRTUAL_GRID_HEIGHT = 128;

const uint U_STAGGERED_GRID_WIDTH = VIRTUAL_GRID_WIDTH+1;
const uint U_STAGGERED_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+2;

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer UQuantity {
    float u[];
};

void main() {
    // Invoke workgroup (0 ~ N, 1, 1)
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x, gl_WorkGroupID.y);
    if (accurate_workgroup_xy.x > 0) {
        // (1, 0) ~ (N, 0)
        u[(accurate_workgroup_xy.x + 1) * U_STAGGERED_GRID_WIDTH] = 0.0;
        // (1, N) ~ (N, N)
        u[(accurate_workgroup_xy.x + 1) * U_STAGGERED_GRID_WIDTH + VIRTUAL_GRID_WIDTH] = 0.0;
    }
    // (0, 0) ~ (0, N)
    u[accurate_workgroup_xy.x] = u[accurate_workgroup_xy.x + U_STAGGERED_GRID_WIDTH];
    // (N+1, 0) ~ (N+1, N)
    u[(VIRTUAL_GRID_HEIGHT+1) * U_STAGGERED_GRID_WIDTH + accurate_workgroup_xy.x] = u[VIRTUAL_GRID_HEIGHT * U_STAGGERED_GRID_WIDTH + accurate_workgroup_xy.x];
}
