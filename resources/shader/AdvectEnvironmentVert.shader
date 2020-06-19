#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

const uint VIRTUAL_GRID_WIDTH = 128;
const uint VIRTUAL_GRID_HEIGHT = 128;

const uint ACTUAL_GRID_WIDTH = VIRTUAL_GRID_WIDTH+2;
const uint ACTUAL_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+2;

const uint U_STAGGERED_GRID_WIDTH = VIRTUAL_GRID_WIDTH+1;
const uint U_STAGGERED_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+2;

const uint V_STAGGERED_GRID_WIDTH = VIRTUAL_GRID_WIDTH+2;
const uint V_STAGGERED_GRID_HEIGHT = VIRTUAL_GRID_HEIGHT+1;

layout(std430, binding = 0) buffer UQuantity {
    float u[];
};

layout(std430, binding = 1) buffer VQuantity {
    float v[];
};

layout(location = 0) in vec3 vCoord;
layout(location = 2) in vec2 vTexCoord;

layout(location = 0) out vec2 fTexCoord;
layout(location = 1) out vec2 fVelocity;

uint indexOfVelocityU(uvec2 grid_xy) {
    return grid_xy.y * U_STAGGERED_GRID_WIDTH + grid_xy.x;
}

uint indexOfVelocityV(uvec2 grid_xy) {
    return grid_xy.y * V_STAGGERED_GRID_WIDTH + grid_xy.x;
}

void main() {
    gl_Position = vec4(vCoord, 1.0);
    fTexCoord = vTexCoord;

    uvec2 accurate_xy = uvec2(fTexCoord*vec2(VIRTUAL_GRID_HEIGHT, VIRTUAL_GRID_WIDTH)+vec2(1));
    fVelocity = vec2(u[indexOfVelocityU(accurate_xy)], v[indexOfVelocityV(accurate_xy)]);
}
