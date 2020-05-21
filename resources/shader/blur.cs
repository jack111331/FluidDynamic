#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

layout(std430, binding=0) buffer Density {
    float density[];
};

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

void main() {
    uint gid = gl_GlobalInvocationID.x;
    density[gid] = 0;
}
