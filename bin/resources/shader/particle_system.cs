#version 450 core
//#extension GL_ARB_shader_storage_buffer_object: enable

layout(std430, binding=0) buffer Pos {
    vec4 Positions[];
};

layout(std430, binding=1) buffer Vel {
    vec4 Velocities[];
};

layout(std430, binding=2) buffer Col {
    vec4 Colors[];
};

layout(local_size_x = 1) in;

const vec3 G = vec3(0., -9.8, 0.);
const float dt = 0.01;

const vec4 SPHERE = vec4(.0, .0, .0, 2.);

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
void main() {

    uint gid = gl_GlobalInvocationID.x;

    vec3 p = Positions[gid].xyz;
    vec3 v = Velocities[gid].xyz;

    vec3 pp = p+v*dt + 0.5*dt*dt*G;
    vec3 vp = v + dt*G;

    if(isInsideSphere(pp, SPHERE)) {
        vp = BounceSphere(p, v, SPHERE);
        pp = p + vp*dt + 0.5 * dt * dt * G;
    }
    if(pp.x > abs(0.8)) {
        vp.x = -vp.x;
    }
    if(pp.y > abs(0.8)) {
        vp.y = -vp.y;
    }

    Positions[gid].xyz = pp;
    Velocities[gid].xyz = vp;
}
