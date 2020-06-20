#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

// one thread each work group

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer UQuantity {
    float u[];
};

layout(std430, binding = 1) buffer VQuantity {
    float v[];
};

layout(std430, binding = 2) buffer PrevUQuantity {
    float prevU[];
};

layout(std430, binding = 3) buffer PrevVQuantity {
    float prevV[];
};

uniform float gridSize;
uniform float vorticity;
uniform float dt;

uint indexOfVelocityU(uvec2 grid_xy);
uint indexOfVelocityV(uvec2 grid_xy);

float dVOverDX(uvec2 grid_xy) {
    return (prevV[indexOfVelocityV(grid_xy)] - prevV[indexOfVelocityV(uvec2(grid_xy.x-1, grid_xy.y))]) / gridSize;
}

float dUOverDY(uvec2 grid_xy) {
    return (prevU[indexOfVelocityU(grid_xy)] - prevU[indexOfVelocityU(uvec2(grid_xy.x, grid_xy.y-1))]) / gridSize;
}

float curl(uvec2 grid_xy) {
    return dVOverDX(grid_xy) - dUOverDY(grid_xy);
}

void main() {
    // Invoke workgroup (N-2, N-2, 1)
    uvec2 accurate_workgroup_xy = uvec2(gl_WorkGroupID.x+2, gl_WorkGroupID.y+2);

    float curlW = curl(accurate_workgroup_xy);
    float curlU = curl(uvec2(accurate_workgroup_xy.x, accurate_workgroup_xy.y-1));
    float curlV = curl(uvec2(accurate_workgroup_xy.x-1, accurate_workgroup_xy.y));
    // FIXME nablaW check
    vec2 nablaW = vec2(abs(curlW - curlU) / gridSize, abs(curlW - curlV) / gridSize);
    if(length(nablaW) != 0.0) {
        nablaW = normalize(nablaW);
        vec2 force = vec2(vorticity * nablaW.y * curlW, vorticity * -nablaW.x * curlW);
        u[indexOfVelocityU(accurate_workgroup_xy)] = prevU[indexOfVelocityU(accurate_workgroup_xy)] + dt * force.x;
        v[indexOfVelocityV(accurate_workgroup_xy)] = prevV[indexOfVelocityV(accurate_workgroup_xy)] + dt * force.y;
    }
}
