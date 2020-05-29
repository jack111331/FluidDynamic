#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

#define GRID_WIDTH 256+2
#define GRID_HEIGHT 256+2

// one thread each work group

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer Density {
    float density[];
};

void main() {
    const uint grid_xy = gl_WorkGroupID.y * GRID_HEIGHT + gl_WorkGroupID.x;
    density[grid_xy] = 0;
}
