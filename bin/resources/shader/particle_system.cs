#version 450 core
#extension GL_ARB_shader_storage_buffer_object: enable

layout( std140, binding=3 ) uniform atomic_uint bounceCount;

/*
layout(std140, binding=4) buffer Pos {
    vec4 Positions[];
};

layout(std140, binding=5) buffer Vel {
    vec4 Velocities[];
};

layout(std140, binding=6) buffer Col {
    vec4 Colors[];
};
*/
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
/*
const vec3 G = vec3(0., -9.8, 0.);
const float dt = 0.1;

const vec4 SPHERE = vec4(-100., -800., 0., 600.);

vec3 Bounce(vec3 vin, vec3 n) {
    vec3 vout = reflect(vin, n);
    return vout;
}

vec3 BounceSphere(vec3 p, vec3 v, vec4 s) {
    vec3 n = normalize(p-s.xyz);
    return Bounce(v, n);
}

bool isInsideSphere(vec3 p, vec4 s) {
    float r = length(p - s.xyz);
    return (r < s.w);
}
*/
void main() {
    atomicCounterIncrement( bounceCount );
    /*
    uint gid = gl_GlobalInvocationID.x;

    vec3 p = Positions[gid].xyz;
    vec3 v = Velocities[gid].xyz;

    vec3 pp = p+v*dt + 0.5*dt*dt*G;
    vec3 vp = v + dt*G;

    if(isInsideSphere(pp, SPHERE)) {
        vp = BounceSphere(p, v, SPHERE);
        pp = p + vp*dt + 0.5 * dt * dt * G;
    }

    Positions[gid].xyz = pp;
    Velocities[gid].xyz = vp;
    */
}
