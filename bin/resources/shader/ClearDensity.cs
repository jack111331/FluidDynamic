#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable
#define GRID_WIDTH 256+2
#define GRID_HEIGHT 256+2

const ivec2 gridSize = ivec2(GRID_WIDTH, GRID_HEIGHT);

layout(local_size_x = GRID_WIDTH, local_size_y = GRID_HEIGHT) in;
layout(std430, binding=0) buffer Density {
    float density[];
}

void main() {
    const ivec2 grid_xy = ivec2(gl_WorkGroupID);
    const ivec2 thread_xy = ivec2(gl_LocalInvocationID);
    const ivec2 pixel_xy = grid_xy * gridSize + thread_xy;
    density[pixel_xy] = 0;
}
