#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

// one thread each work group

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer Pressure {
    float pressure[];
};

layout(std430, binding = 1) buffer Divergence {
    float divergence[];
};

layout(std430, binding = 2) buffer UQuantity {
    float u[];
};

layout(std430, binding = 3) buffer VQuantity {
    float v[];
};

uniform float gridSize;

uint indexOfVelocityU(uvec2 grid_xy);
uint indexOfVelocityV(uvec2 grid_xy);
uint indexOfPressure(uvec2 grid_xy);

void main() {
    // Invoke workgroup (N, N, 1)
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x+1, gl_WorkGroupID.y+1);
    divergence[indexOfPressure(accurate_workgroup_xy)] =
    -(u[indexOfVelocityU(accurate_workgroup_xy)] - u[indexOfVelocityU(uvec2(accurate_workgroup_xy.x-1, accurate_workgroup_xy.y))] + v[indexOfVelocityV(accurate_workgroup_xy)] - v[indexOfVelocityV(uvec2(accurate_workgroup_xy.x, accurate_workgroup_xy.y-1))]) / gridSize;
    pressure[indexOfPressure(accurate_workgroup_xy)] = 0.0;
}
