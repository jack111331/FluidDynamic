#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

#define V_STAGGERED_GRID_WIDTH 256+2
#define V_STAGGERED_GRID_HEIGHT 256+1

uint indexOfVelocityV(uvec2 grid_xy) {
    return grid_xy.y * V_STAGGERED_GRID_WIDTH + grid_xy.x;
}
