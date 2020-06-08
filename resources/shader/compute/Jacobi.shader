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
layout(std430, binding = 1) buffer Divergence {
    float divergence[];
};
layout(std430, binding = 2) buffer DensityOutput {
    float densityOutput[];
};

uniform float a;
uniform float denom;

void main() {
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x+1, gl_WorkGroupID.y+1);
    densityOutput[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x] = (density[(accurate_workgroup_xy.y+1) * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x] + density[(accurate_workgroup_xy.y-1) * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x] +
    density[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x + 1] + density[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x - 1] + a * divergence[accurate_workgroup_xy.y * ACTUAL_GRID_WIDTH + accurate_workgroup_xy.x]) / denom;
}
