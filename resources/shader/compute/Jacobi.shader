#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

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

uint indexOfPressure(uvec2 grid_xy);

void main() {
    // Invoke workgroup (N, N, 1)
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x+1, gl_WorkGroupID.y+1);
    densityOutput[indexOfPressure(accurate_workgroup_xy)] = (density[indexOfPressure(uvec2(accurate_workgroup_xy.x, accurate_workgroup_xy.y+1))] + density[indexOfPressure(uvec2(accurate_workgroup_xy.x, accurate_workgroup_xy.y-1))] +
    density[indexOfPressure(uvec2(accurate_workgroup_xy.x+1, accurate_workgroup_xy.y))] + density[indexOfPressure(uvec2(accurate_workgroup_xy.x-1, accurate_workgroup_xy.y))] + a * divergence[indexOfPressure(accurate_workgroup_xy)]) / denom;
}
