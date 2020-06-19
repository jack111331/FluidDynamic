#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

float linearInterpolate2D(vec2 portion, float ll, float lr, float ul, float ur) {
     return (1 - portion.y) * ((1 - portion.x) * ll + portion.x * lr) + portion.y * ((1 - portion.x) * ul + portion.x * ur);
}

vec4 linearInterpolate2D(vec2 portion, vec4 ll, vec4 lr, vec4 ul, vec4 ur) {
     return (1 - portion.y) * ((1 - portion.x) * ll + portion.x * lr) + portion.y * ((1 - portion.x) * ul + portion.x * ur);
}