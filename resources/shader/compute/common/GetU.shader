#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

#define U_STAGGERED_GRID_WIDTH 256+1
#define U_STAGGERED_GRID_HEIGHT 256+2

uint indexOfVelocityU(uvec2 grid_xy) {
    return grid_xy.y * U_STAGGERED_GRID_WIDTH + grid_xy.x;
}
