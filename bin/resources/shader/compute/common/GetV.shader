#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

#define U_STAGGERED_GRID_WIDTH 256+2
#define U_STAGGERED_GRID_HEIGHT 256+1

uint indexOfVelocityV(uvec2 grid_xy) {
    return dot(grid_xy, uvec2(1, GRID_WIDTH));
}
