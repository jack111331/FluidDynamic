#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

const uint VIRTUAL_GRID_WIDTH = 256;
const uint VIRTUAL_GRID_HEIGHT = 256;

const uint V_STAGGERED_GRID_WIDTH = VIRTUAL_GRID_WIDTH+2;
const uint V_STAGGERED_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+1;

uint indexOfVelocityV(uvec2 grid_xy) {
    return grid_xy.y * (V_STAGGERED_GRID_WIDTH) + grid_xy.x;
}
