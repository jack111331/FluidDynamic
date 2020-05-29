#include "Density.h"
#include "Utility.h"
#include <iostream>
#include <cmath>
#include <GL/glew.h>

Density::Density(int N) : m_grid(N) {
    glGenBuffers(2, m_quantity);
    for (int i = 0; i < 2; ++i) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_quantity[i]);
        glBufferData(GL_SHADER_STORAGE_BUFFER, (N + 2) * (N + 2) * sizeof(float), NULL, GL_DYNAMIC_DRAW);
        clear(i);
    }
}

Density::~Density() {
    glDeleteBuffers(2, m_quantity);
}

void Density::clear(bool isPrevious) {
    // location = 0: quantity
    CLEAR_DENSITY_PROGRAM.bind();
    CLEAR_DENSITY_PROGRAM.bindBuffer(m_quantity[m_currentContext ^ isPrevious], 0);
    CLEAR_DENSITY_PROGRAM.dispatch(m_grid + 2, m_grid + 2, 1);
}

void Density::blur(const float *density, int gridSize, float sigma, float *target) {
    double kernel[9] = {exp(-1 / (sigma * sigma)), exp(-0.5 / (sigma * sigma)), exp(-1 / (sigma * sigma)),
                        exp(-0.5 / (sigma * sigma)), exp(-1), exp(-0.5 / (sigma * sigma)),
                        exp(-1 / (sigma * sigma)), exp(-0.5 / (sigma * sigma)), exp(-1 / (sigma * sigma))
    };
    double total = 0;
    for (int i = 0; i < 9; ++i) {
        total += kernel[i];
    }
    for (int i = 0; i < 9; ++i) {
        kernel[i] /= total;
    }
    for (int i = 1; i <= gridSize; ++i) {
        for (int j = 1; j <= gridSize; ++j) {
            target[indexOf(i, j, gridSize)] =
                    kernel[0] * density[indexOf(i - 1, j - 1, gridSize)]
                    + kernel[1] * density[indexOf(i - 1, j, gridSize)]
                    + kernel[2] * density[indexOf(i - 1, j + 1, gridSize)]
                    + kernel[3] * density[indexOf(i, j - 1, gridSize)]
                    + kernel[4] * density[indexOf(i, j, gridSize)]
                    + kernel[5] * density[indexOf(i, j + 1, gridSize)]
                    + kernel[6] * density[indexOf(i + 1, j - 1, gridSize)]
                    + kernel[7] * density[indexOf(i + 1, j, gridSize)]
                    + kernel[8] * density[indexOf(i + 1, j + 1, gridSize)];
        }
    }
}

void Density::addQuantity(float dt) {
    // location = 0: current quantity
    // location = 1: previous quantity
    ADD_DENSITY_PROGRAM.bind();
    ADD_DENSITY_PROGRAM.bindBuffer(m_quantity[m_currentContext], 0);
    ADD_DENSITY_PROGRAM.bindBuffer(m_quantity[m_currentContext ^ 1], 1);
    ADD_DENSITY_PROGRAM.uniform1f("dt", dt);
    ADD_DENSITY_PROGRAM.dispatch(m_grid + 2, m_grid + 2, 1);

}

void Density::diffuse(float dt, float diffusion) {
    GaussSeidelSolver *solver = new GaussSeidelSolver(20);
    float diffusionForNearbyGrid = dt * diffusion * m_grid * m_grid;
    solver->solve(m_quantity[m_currentContext], m_quantity[m_currentContext ^ 1], diffusionForNearbyGrid,
                  (1 + 4 * diffusionForNearbyGrid));
    delete solver;
}

void Density::advect(float dt, uint32_t u, uint32_t v) {
    // location = 0: current quantity
    // location = 1: previous quantity
    // location = 2: current u vector field
    // location = 3: current v vector field
    ADVECT_DENSITY_PROGRAM.bind();
    ADVECT_DENSITY_PROGRAM.bindBuffer(m_quantity[m_currentContext], 0);
    ADVECT_DENSITY_PROGRAM.bindBuffer(m_quantity[m_currentContext ^ 1], 1);
    ADVECT_DENSITY_PROGRAM.bindBuffer(u, 2);
    ADVECT_DENSITY_PROGRAM.bindBuffer(v, 3);
    ADVECT_DENSITY_PROGRAM.uniform1f("dt0", dt * m_grid);
    ADVECT_DENSITY_PROGRAM.dispatch(m_grid, m_grid, 1);

    ShaderUtility::SET_DENSITY_BOUND_PROGRAM.bind();
    ShaderUtility::SET_DENSITY_BOUND_PROGRAM.bindBuffer(m_quantity[m_currentContext], 0);
    ShaderUtility::SET_DENSITY_BOUND_PROGRAM.dispatch(m_grid, 1, 1);
}

void Density::process(float dt, float diffusion, uint32_t u, uint32_t v) {
    addQuantity(dt);

    m_currentContext ^= 1;
    diffuse(dt, diffusion);

    m_currentContext ^= 1;
    advect(dt, u, v);
}

uint32_t Density::getQuantity() {
    return m_quantity[m_currentContext];
}

uint32_t Density::getPrevQuantity() {
    return m_quantity[m_currentContext ^ 1];
}
