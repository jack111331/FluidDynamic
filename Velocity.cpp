#include "Velocity.h"
#include "Utility.h"
#include "Solver.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>

using namespace std;

Velocity::Velocity(int N) : m_grid(N), m_currentContext(0) {
    glGenBuffers(2, m_uQuantity);
    glGenBuffers(2, m_vQuantity);
    for (int i = 0; i < 2; ++i) {
        // m_uQuantity[indexOfVelocityU(i, j, m_grid)] = u_(i, j-1/2)
        // m_vQuantity[indexOfVelocityV(i, j, m_grid)] = v_(i-1/2, j)


        // Extend upper and lower as boundary
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_uQuantity[i]);
        glBufferData(GL_SHADER_STORAGE_BUFFER, (N + 2) * (N + 1) * sizeof(float), NULL, GL_DYNAMIC_DRAW);
        // Extend left and right as boundary
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_vQuantity[i]);
        glBufferData(GL_SHADER_STORAGE_BUFFER, (N + 1) * (N + 2) * sizeof(float), NULL, GL_DYNAMIC_DRAW);
        clear(i);
    }
}

Velocity::~Velocity() {
    glDeleteBuffers(2, m_uQuantity);
    glDeleteBuffers(2, m_vQuantity);
}

void Velocity::clear(bool isPrevious) {
    // location = 0: U component quantity
    // location = 1: V component quantity
    CLEAR_VELOCITY_PROGRAM.bind();
    CLEAR_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext ^ isPrevious], 0);
    CLEAR_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext ^ isPrevious], 1);
    CLEAR_VELOCITY_PROGRAM.dispatch(1, 1, 1);
}

void Velocity::addForce(float dt) {
    // location = 0: current U component quantity
    // location = 1: previous U component quantity
    // location = 2: current V component quantity
    // location = 3: previous V component quantity
    ADD_VELOCITY_PROGRAM.bind();
    ADD_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    ADD_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext ^ 1], 1);
    ADD_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 2);
    ADD_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext ^ 1], 3);
    ADD_VELOCITY_PROGRAM.uniform1f("dt", dt);
    ADD_VELOCITY_PROGRAM.dispatch(1, 1, 1);

    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.bind();
    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.dispatch(1, 1, 1);

    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.bind();
    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 0);
    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.dispatch(1, 1, 1);
}

void Velocity::advectU(float dt) {
    // location = 0: current U component quantity
    // location = 1: previous U component quantity
    // location = 2: previous V component quantity
    ADVECT_U_VELOCITY_PROGRAM.bind();
    ADVECT_U_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    ADVECT_U_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext ^ 1], 1);
    ADVECT_U_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext ^ 1], 2);
    ADVECT_U_VELOCITY_PROGRAM.uniform1f("dt", dt);
    ADVECT_U_VELOCITY_PROGRAM.dispatch(1, 1, 1);

    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.bind();
    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.dispatch(1, 1, 1);
}

void Velocity::advectV(float dt) {
    // location = 0: current V component quantity
    // location = 1: previous U component quantity
    // location = 2: previous V component quantity
    ADVECT_V_VELOCITY_PROGRAM.bind();
    ADVECT_V_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 0);
    ADVECT_V_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext ^ 1], 1);
    ADVECT_V_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext ^ 1], 2);
    ADVECT_V_VELOCITY_PROGRAM.uniform1f("dt", dt);
    ADVECT_V_VELOCITY_PROGRAM.dispatch(1, 1, 1);

    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.bind();
    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 0);
    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.dispatch(1, 1, 1);
}

void Velocity::vorticityConfinement(float dt, float vorticity) {
    // location = 0: current U component quantity
    // location = 1: current V component quantity
    // location = 2: previous U component quantity
    // location = 3: previous V component quantity
    CONFINE_VORTICITY_VELOCITY_PROGRAM.bind();
    CONFINE_VORTICITY_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    CONFINE_VORTICITY_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 1);
    CONFINE_VORTICITY_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext ^ 1], 2);
    CONFINE_VORTICITY_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext ^ 1], 3);
    CONFINE_VORTICITY_VELOCITY_PROGRAM.uniform1f("dt", dt);
    CONFINE_VORTICITY_VELOCITY_PROGRAM.uniform1f("vorticity", vorticity);
    CONFINE_VORTICITY_VELOCITY_PROGRAM.dispatch(1, 1, 1);

    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.bind();
    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.dispatch(1, 1, 1);

    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.bind();
    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 0);
    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.dispatch(1, 1, 1);
}


void Velocity::massConserve(float dt) {
    // Use Gauss Seidel
    GaussSeidelSolver *solver = new GaussSeidelSolver();
    uint32_t p, prevP;
    glGenBuffers(1, &p);
    glGenBuffers(1, &prevP);
    // Extend upper and lower as boundary
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, p);
    glBufferData(GL_SHADER_STORAGE_BUFFER, (m_grid + 2) * (m_grid + 2) * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, prevP);
    glBufferData(GL_SHADER_STORAGE_BUFFER, (m_grid + 2) * (m_grid + 2) * sizeof(float), NULL, GL_DYNAMIC_DRAW);

    // location = 0: current Pressure quantity
    // location = 1: previous Pressure quantity
    // location = 2: current U component quantity
    // location = 3: current V component quantity
    BUILD_PRESSURE_PROGRAM.bind();
    BUILD_PRESSURE_PROGRAM.bindBuffer(p, 0);
    BUILD_PRESSURE_PROGRAM.bindBuffer(prevP, 1);
    BUILD_PRESSURE_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 2);
    BUILD_PRESSURE_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 3);
    BUILD_PRESSURE_PROGRAM.uniform1f("inv", (float)1/(float)m_grid);
    BUILD_PRESSURE_PROGRAM.dispatch(1, 1, 1);

    ShaderUtility::SET_DENSITY_BOUND_PROGRAM.bind();
    ShaderUtility::SET_DENSITY_BOUND_PROGRAM.bindBuffer(p, 0);
    ShaderUtility::SET_DENSITY_BOUND_PROGRAM.dispatch(1, 1, 1);

    ShaderUtility::SET_DENSITY_BOUND_PROGRAM.bindBuffer(prevP, 0);
    ShaderUtility::SET_DENSITY_BOUND_PROGRAM.dispatch(1, 1, 1);

    solver->solve(p, prevP, 1.0f, 4.0f);

    // location = 0: current U component quantity
    // location = 1: current V component quantity
    // location = 2: current Pressure quantity
    CONSERVE_MASS_PROGRAM.bind();
    CONSERVE_MASS_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    CONSERVE_MASS_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 1);
    CONSERVE_MASS_PROGRAM.bindBuffer(p, 2);
    CONSERVE_MASS_PROGRAM.uniform1f("gridSize", m_grid);
    CONSERVE_MASS_PROGRAM.dispatch(1, 1, 1);
    glDeleteBuffers(1, &p);
    glDeleteBuffers(1, &prevP);
    delete solver;

    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.bind();
    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.dispatch(1, 1, 1);

    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.bind();
    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 0);
    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.dispatch(1, 1, 1);

}

void Velocity::process(float dt, float vorticity) {
    // Add force
    addForce(dt);
    // Mass conservative
    massConserve(dt);

    m_currentContext ^= 1;
    vorticityConfinement(dt, vorticity);
    massConserve(dt);

    m_currentContext ^= 1;
    advectU(dt);
    advectV(dt);

    // Mass conservative
    massConserve(dt);
}

uint32_t Velocity::getQuantity(int component) {
    if (component == U_COMPONENT) {
        return m_uQuantity[m_currentContext];
    } else if (component == V_COMPONENT) {
        return m_vQuantity[m_currentContext];
    }
}

uint32_t Velocity::getPrevQuantity(int component) {
    if (component == U_COMPONENT) {
        return m_uQuantity[m_currentContext ^ 1];
    } else if (component == V_COMPONENT) {
        return m_vQuantity[m_currentContext ^ 1];
    }
}
