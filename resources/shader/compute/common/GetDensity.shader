#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

const uint VIRTUAL_GRID_WIDTH = 256;
const uint VIRTUAL_GRID_HEIGHT = 256;

const uint ACTUAL_GRID_WIDTH = VIRTUAL_GRID_WIDTH+2;
const uint ACTUAL_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+2;

uint indexOfPressure(uvec2 grid_xy) {
    return grid_xy.y * (ACTUAL_GRID_WIDTH) + grid_xy.x;
}
