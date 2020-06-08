#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

const uint VIRTUAL_GRID_WIDTH = 256;
const uint VIRTUAL_GRID_HEIGHT = 256;

const uint ACTUAL_GRID_WIDTH = VIRTUAL_GRID_WIDTH+2;
const uint ACTUAL_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+2;

// one thread each work group

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer Density {
    float density[];
};
layout(std430, binding = 1) buffer PrevDensity {
    float prevDensity[];
};

uniform float dt;

void main() {
    const uint grid_xy = gl_WorkGroupID.y * ACTUAL_GRID_HEIGHT + gl_WorkGroupID.x;
    density[grid_xy] += dt * prevDensity[grid_xy];
}
