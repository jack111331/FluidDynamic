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

layout(location = 0) in vec2 fTexCoord;

layout(std430, binding = 0) buffer UQuantity {
    float u[];
};

layout(std430, binding = 1) buffer VQuantity {
    float v[];
};

layout(location = 0) out vec4 fVelocity;

uint indexOfVelocityU(uvec2 grid_xy) {
    return grid_xy.y * U_STAGGERED_GRID_WIDTH + grid_xy.x;
}

uint indexOfVelocityV(uvec2 grid_xy) {
    return grid_xy.y * V_STAGGERED_GRID_WIDTH + grid_xy.x;
}

float linearInterpolate1D(float portion, float l, float r) {
    return portion * r + (1 - portion) * l;
}

float linearInterpolate2D(vec2 portion, float ll, float lr, float ul, float ur) {
    return (1 - portion.y) * ((1 - portion.x) * ll + portion.x * lr) + portion.y * ((1 - portion.x) * ul + portion.x * ur);
}

void main() {
    // map from (0.0, 1.0) to (gridSize, gridSize)
    vec2 grid_xy = fTexCoord * vec2(VIRTUAL_GRID_WIDTH, VIRTUAL_GRID_HEIGHT);// + vec2(1.0);
    uvec2 alligned_grid_xy = uvec2(grid_xy);
    // interpolate between grid
    fVelocity = vec4(
        linearInterpolate1D(grid_xy.x - alligned_grid_xy.x, u[indexOfVelocityU(alligned_grid_xy)], u[indexOfVelocityU(uvec2(alligned_grid_xy.x+1, alligned_grid_xy.y))]),
        linearInterpolate1D(grid_xy.y - alligned_grid_xy.y, v[indexOfVelocityV(alligned_grid_xy)], v[indexOfVelocityV(uvec2(alligned_grid_xy.x, alligned_grid_xy.y+1))]),
        0.0,
        0.0
    );
}
