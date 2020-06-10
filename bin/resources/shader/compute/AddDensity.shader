#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

const uint VIRTUAL_GRID_WIDTH = 128;
const uint VIRTUAL_GRID_HEIGHT = 128;

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
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x + 1, gl_WorkGroupID.y + 1);
    const uint grid_xy = accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x;
    density[grid_xy] += dt * prevDensity[grid_xy];
}
