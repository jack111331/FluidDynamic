#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable
// TODO refactor
const uint VIRTUAL_GRID_WIDTH = 128;
const uint VIRTUAL_GRID_HEIGHT = 128;

const uint V_STAGGERED_GRID_WIDTH = VIRTUAL_GRID_WIDTH+2;
const uint V_STAGGERED_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+1;

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer VQuantity {
    float v[];
};

void main() {
    // Invoke workgroup (0 ~ N, 1, 1)
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x, gl_WorkGroupID.y);
    if (accurate_workgroup_xy.x > 0) {
        // (0, 1) ~ (0, N)
        v[accurate_workgroup_xy.x] = 0.0;
        // (N, 1) ~ (N, N)
        v[VIRTUAL_GRID_HEIGHT * V_STAGGERED_GRID_WIDTH + accurate_workgroup_xy.x] = 0.0;
    }
    // (0, 0) ~ (N, 0)
    v[accurate_workgroup_xy.x * V_STAGGERED_GRID_WIDTH] = v[accurate_workgroup_xy.x * V_STAGGERED_GRID_WIDTH + 1];
    // (0, N+1) ~ (N, N+1)
    v[accurate_workgroup_xy.x * V_STAGGERED_GRID_WIDTH + VIRTUAL_GRID_WIDTH + 1] = v[accurate_workgroup_xy.x * V_STAGGERED_GRID_WIDTH + VIRTUAL_GRID_WIDTH];
}
