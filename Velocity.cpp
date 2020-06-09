#include "Velocity.h"
#include "Utility.h"
#include "Solver.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>

using namespace std;


Velocity::Velocity(int N) : m_grid(N), m_currentContext(false) {
    m_shaderUtility = ShaderUtility::getInstance();
    m_solver = new JacobiSolver();

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
    delete m_solver;
}

void Velocity::clear(bool isPrevious) {
    m_shaderUtility->CLEAR_VELOCITY_PROGRAM.bind();
    m_shaderUtility->CLEAR_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext ^ isPrevious], 0);
    m_shaderUtility->CLEAR_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext ^ isPrevious], 1);
    m_shaderUtility->CLEAR_VELOCITY_PROGRAM.dispatch(m_grid + 1, m_grid + 2, 1);
}

void Velocity::addForce(float dt) {
    m_shaderUtility->ADD_VELOCITY_PROGRAM.bind();
    m_shaderUtility->ADD_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    m_shaderUtility->ADD_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext ^ 1], 1);
    m_shaderUtility->ADD_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 2);
    m_shaderUtility->ADD_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext ^ 1], 3);
    m_shaderUtility->ADD_VELOCITY_PROGRAM.uniform1f("dt", dt);
    m_shaderUtility->ADD_VELOCITY_PROGRAM.dispatch(m_grid - 1, m_grid, 1);

    ShaderUtility::getInstance()->SET_U_VELOCITY_BOUND_PROGRAM.bind();
    ShaderUtility::getInstance()->SET_U_VELOCITY_BOUND_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    ShaderUtility::getInstance()->SET_U_VELOCITY_BOUND_PROGRAM.dispatch(m_grid + 1, 1, 1);

    ShaderUtility::getInstance()->SET_V_VELOCITY_BOUND_PROGRAM.bind();
    ShaderUtility::getInstance()->SET_V_VELOCITY_BOUND_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 0);
    ShaderUtility::getInstance()->SET_V_VELOCITY_BOUND_PROGRAM.dispatch(m_grid + 1, 1, 1);
}

void Velocity::advectU(float dt) {

    m_shaderUtility->ADVECT_U_VELOCITY_PROGRAM.bind();
    m_shaderUtility->ADVECT_U_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    m_shaderUtility->ADVECT_U_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext ^ 1], 1);
    m_shaderUtility->ADVECT_U_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext ^ 1], 2);
    m_shaderUtility->ADVECT_U_VELOCITY_PROGRAM.uniform1f("dt0", dt * m_grid);
    m_shaderUtility->ADVECT_U_VELOCITY_PROGRAM.dispatch(m_grid - 1, m_grid, 1);

    m_shaderUtility->SET_U_VELOCITY_BOUND_PROGRAM.bind();
    m_shaderUtility->SET_U_VELOCITY_BOUND_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    m_shaderUtility->SET_U_VELOCITY_BOUND_PROGRAM.dispatch(m_grid + 1, 1, 1);
}

void Velocity::advectV(float dt) {
    m_shaderUtility->ADVECT_V_VELOCITY_PROGRAM.bind();
    m_shaderUtility->ADVECT_V_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 0);
    m_shaderUtility->ADVECT_V_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext ^ 1], 1);
    m_shaderUtility->ADVECT_V_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext ^ 1], 2);
    m_shaderUtility->ADVECT_V_VELOCITY_PROGRAM.uniform1f("dt0", dt * m_grid);
    m_shaderUtility->ADVECT_V_VELOCITY_PROGRAM.dispatch(m_grid, m_grid - 1, 1);

    m_shaderUtility->SET_V_VELOCITY_BOUND_PROGRAM.bind();
    m_shaderUtility->SET_V_VELOCITY_BOUND_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 0);
    m_shaderUtility->SET_V_VELOCITY_BOUND_PROGRAM.dispatch(m_grid + 1, 1, 1);
}

//void Velocity::vorticityConfinement(float dt, float vorticity) {
//    CONFINE_VORTICITY_VELOCITY_PROGRAM.bind();
//    CONFINE_VORTICITY_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
//    CONFINE_VORTICITY_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 1);
//    CONFINE_VORTICITY_VELOCITY_PROGRAM.bindBuffer(m_uQuantity[m_currentContext ^ 1], 2);
//    CONFINE_VORTICITY_VELOCITY_PROGRAM.bindBuffer(m_vQuantity[m_currentContext ^ 1], 3);
//    CONFINE_VORTICITY_VELOCITY_PROGRAM.uniform1f("dt", dt);
//    CONFINE_VORTICITY_VELOCITY_PROGRAM.uniform1f("vorticity", vorticity);
//    CONFINE_VORTICITY_VELOCITY_PROGRAM.dispatch(1, 1, 1);
//
//    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.bind();
//    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
//    ShaderUtility::SET_U_VELOCITY_BOUND_PROGRAM.dispatch(m_grid+1, 1, 1);
//
//    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.bind();
//    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 0);
//    ShaderUtility::SET_V_VELOCITY_BOUND_PROGRAM.dispatch(m_grid+1, 1, 1);
//}


void Velocity::massConserve() {
    // Use Gauss Seidel
    // GaussSeidelSolver *m_solver = new GaussSeidelSolver();
    uint32_t p, div;
    glGenBuffers(1, &p);
    glGenBuffers(1, &div);
    // Extend upper and lower as boundary
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, p);
    glBufferData(GL_SHADER_STORAGE_BUFFER, (m_grid + 2) * (m_grid + 2) * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, div);
    glBufferData(GL_SHADER_STORAGE_BUFFER, (m_grid + 2) * (m_grid + 2) * sizeof(float), NULL, GL_DYNAMIC_DRAW);

    m_shaderUtility->BUILD_PRESSURE_PROGRAM.bind();
    m_shaderUtility->BUILD_PRESSURE_PROGRAM.bindBuffer(p, 0);
    m_shaderUtility->BUILD_PRESSURE_PROGRAM.bindBuffer(div, 1);
    m_shaderUtility->BUILD_PRESSURE_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 2);
    m_shaderUtility->BUILD_PRESSURE_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 3);
    m_shaderUtility->BUILD_PRESSURE_PROGRAM.uniform1f("gridSize", m_grid);
    m_shaderUtility->BUILD_PRESSURE_PROGRAM.dispatch(m_grid, m_grid, 1);

    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bind();
    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bindBuffer(p, 0);
    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.dispatch(1, 1, 1);

    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bind();
    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bindBuffer(div, 0);
    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.dispatch(1, 1, 1);

    m_solver->solve(p, div, 1.0f, 4.0f, m_grid);

    m_shaderUtility->CONSERVE_MASS_PROGRAM.bind();
    m_shaderUtility->CONSERVE_MASS_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    m_shaderUtility->CONSERVE_MASS_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 1);
    m_shaderUtility->CONSERVE_MASS_PROGRAM.bindBuffer(p, 2);
    m_shaderUtility->CONSERVE_MASS_PROGRAM.uniform1f("gridSize", m_grid);
    m_shaderUtility->CONSERVE_MASS_PROGRAM.dispatch(m_grid - 1, m_grid, 1);
    glDeleteBuffers(1, &p);
    glDeleteBuffers(1, &div);

    m_shaderUtility->SET_U_VELOCITY_BOUND_PROGRAM.bind();
    m_shaderUtility->SET_U_VELOCITY_BOUND_PROGRAM.bindBuffer(m_uQuantity[m_currentContext], 0);
    m_shaderUtility->SET_U_VELOCITY_BOUND_PROGRAM.dispatch(m_grid + 1, 1, 1);

    m_shaderUtility->SET_V_VELOCITY_BOUND_PROGRAM.bind();
    m_shaderUtility->SET_V_VELOCITY_BOUND_PROGRAM.bindBuffer(m_vQuantity[m_currentContext], 0);
    m_shaderUtility->SET_V_VELOCITY_BOUND_PROGRAM.dispatch(m_grid + 1, 1, 1);

}

void Velocity::process(float dt, float vorticity) {
    // Add force
    addForce(dt);
    // Mass conservative
    massConserve();

//    m_currentContext ^= 1;
//    vorticityConfinement(dt, vorticity);
//    massConserve();

//TODO fix advect
    m_currentContext ^= 1;
    advectU(dt);
    advectV(dt);

//     Mass conservative
//    massConserve();
}

float *Velocity::enableAndGetReadWriteQuantity(int component, bool isPrevious) {
    if (component == Velocity::U_COMPONENT) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_uQuantity[m_currentContext ^ isPrevious]);
    } else {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_vQuantity[m_currentContext ^ isPrevious]);
    }
    return (float *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, (m_grid + 2) * (m_grid + 1) * sizeof(float),
                                      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
}

const float *Velocity::enableAndGetReadQuantity(int component, bool isPrevious) {
    if (component == Velocity::U_COMPONENT) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_uQuantity[m_currentContext ^ isPrevious]);
    } else {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_vQuantity[m_currentContext ^ isPrevious]);
    }
    return (float *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, (m_grid + 2) * (m_grid + 1) * sizeof(float),
                                      GL_MAP_READ_BIT);
}

void Velocity::disableReadOrWriteQuantity(int component, bool isPrevious) {
    if (component == Velocity::U_COMPONENT) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_uQuantity[m_currentContext ^ isPrevious]);
    } else {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_vQuantity[m_currentContext ^ isPrevious]);
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

uint32_t Velocity::getBufferId(int component, bool isPrevious) {
    if (component == Velocity::U_COMPONENT) {
        return m_uQuantity[m_currentContext ^ isPrevious];
    } else {
        return m_vQuantity[m_currentContext ^ isPrevious];
    }
}