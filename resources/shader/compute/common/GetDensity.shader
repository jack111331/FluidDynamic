#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

#define GRID_WIDTH 256+2
#define GRID_HEIGHT 256+2

uint indexOfPressure(uvec2 grid_xy) {
    return grid_xy.y * GRID_WIDTH + grid_xy.x;
}
