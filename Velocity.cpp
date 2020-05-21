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
        std::fill_n(m_uQuantity[i], (N + 2) * (N + 1), 0.0f);
        std::fill_n(m_vQuantity[i], (N + 1) * (N + 2), 0.0f);
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
    CLEAR_VELOCITY_PROGRAM.dispatch();
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
    ADD_VELOCITY_PROGRAM.dispatch();
    // TODO set u v boundary
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
    ADVECT_U_VELOCITY_PROGRAM.dispatch();
    // TODO set u boundary
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
    ADVECT_V_VELOCITY_PROGRAM.dispatch();
    // TODO set v boundary
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
    CONFINE_VORTICITY_VELOCITY_PROGRAM.dispatch();
    // TODO set u v boundary
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

void Velocity::massConserve(float dt) {
    // Use Gauss Seidel
    float *p = new float[(m_grid + 2) * (m_grid + 2)], *prevP = new float[(m_grid + 2) * (m_grid + 2)];
    Solver *solver = new GaussSeidelSolver();
    for (int i = 1; i <= m_grid; ++i) {
        for (int j = 1; j <= m_grid; ++j) {
            prevP[indexOfPressure(i, j, m_grid)] = -(m_uQuantity[m_currentContext][indexOfVelocityU(i, j, m_grid)] -
                                                     m_uQuantity[m_currentContext][indexOfVelocityU(i, j - 1, m_grid)] +
                                                     m_vQuantity[m_currentContext][indexOfVelocityV(i, j, m_grid)] -
                                                     m_vQuantity[m_currentContext][indexOfVelocityV(i - 1, j,
                                                                                                    m_grid)]) / m_grid;
            p[indexOfPressure(i, j, m_grid)] = 0.0f;
        }
    }
    setBoundary(0, prevP, m_grid);
    setBoundary(0, p, m_grid);
    solver->solve(p, prevP, 1.0f, 4.0f, 0, m_grid);
    // TODO set boundary
    for (int i = 1; i <= m_grid; ++i) {
        for (int j = 1; j <= m_grid - 1; ++j) {
            m_uQuantity[m_currentContext][indexOfVelocityU(i, j, m_grid)] -=
                    m_grid * (p[indexOfPressure(i, j + 1, m_grid)] - p[indexOfPressure(i, j, m_grid)]);
        }
    }
    for (int i = 1; i <= m_grid - 1; ++i) {
        for (int j = 1; j <= m_grid; ++j) {
            m_vQuantity[m_currentContext][indexOfVelocityV(i, j, m_grid)] -=
                    m_grid * (p[indexOfPressure(i + 1, j, m_grid)] - p[indexOfPressure(i, j, m_grid)]);
        }
    }
    delete[] prevP;
    delete[] p;
    delete solver;
    setUBoundary(m_uQuantity[m_currentContext], m_grid);
    setVBoundary(m_vQuantity[m_currentContext], m_grid);

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
