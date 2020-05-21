#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

layout(std430, binding=0) buffer Density {
    float density[];
};

layout(local_size_x = gl_WorkGroupSize.x, local_size_y = gl_WorkGroupSize.y, local_size_z = gl_WorkGroupSize.z) in;

void main() {
    uint gid = gl_GlobalInvocationID.x;
    density[gid] = 0;
}
