#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

const uint VIRTUAL_GRID_WIDTH = 256;
const uint VIRTUAL_GRID_HEIGHT = 256;

const uint U_STAGGERED_GRID_WIDTH = VIRTUAL_GRID_WIDTH+1;
const uint U_STAGGERED_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+2;

const uint V_STAGGERED_GRID_WIDTH = VIRTUAL_GRID_WIDTH+2;
const uint V_STAGGERED_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+1;

// one thread each work group

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer UQuantity {
    float u[];
};

layout(std430, binding = 1) buffer VQuantity {
    float v[];
};

void main() {
    // Invoke workgroup (N+1, N+2, 1)
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x, gl_WorkGroupID.y);
    u[accurate_workgroup_xy.y * U_STAGGERED_GRID_WIDTH + accurate_workgroup_xy.x] = 0;
    v[accurate_workgroup_xy.x * V_STAGGERED_GRID_WIDTH + accurate_workgroup_xy.y] = 0;
}
