#include "Density.h"
#include "Utility.h"
#include <iostream>
#include <cmath>
#include <GL/glew.h>

Density::Density(int N) : m_grid(N) {
    m_shaderUtility = ShaderUtility::getInstance();
    m_solver = new JacobiSolver(20);

    glGenBuffers(2, m_quantity);
    for (int i = 0; i < 2; ++i) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_quantity[i]);
        glBufferData(GL_SHADER_STORAGE_BUFFER, (N + 2) * (N + 2) * sizeof(float), NULL, GL_DYNAMIC_DRAW);
        clear(i);
    }
}

Density::~Density() {
    glDeleteBuffers(2, m_quantity);
    delete m_solver;
}

void Density::clear(bool isPrevious) {
    m_shaderUtility->CLEAR_DENSITY_PROGRAM.bind();
    m_shaderUtility->CLEAR_DENSITY_PROGRAM.bindBuffer(m_quantity[m_currentContext ^ isPrevious], 0);
    m_shaderUtility->CLEAR_DENSITY_PROGRAM.dispatch(m_grid + 2, m_grid + 2, 1);
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
    m_shaderUtility->ADD_DENSITY_PROGRAM.bind();
    m_shaderUtility->ADD_DENSITY_PROGRAM.bindBuffer(m_quantity[m_currentContext], 0);
    m_shaderUtility->ADD_DENSITY_PROGRAM.bindBuffer(m_quantity[m_currentContext ^ 1], 1);
    m_shaderUtility->ADD_DENSITY_PROGRAM.uniform1f("dt", dt);
    m_shaderUtility->ADD_DENSITY_PROGRAM.dispatch(m_grid + 2, m_grid + 2, 1);
}

void Density::diffuse(float dt, float diffusion) {
//    GaussSeidelSolver *m_solver = new GaussSeidelSolver(20);

    float diffusionForNearbyGrid = dt * diffusion * m_grid * m_grid;
    uint32_t temp;
    glGenBuffers(1, &temp);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, temp);
    glBufferData(GL_SHADER_STORAGE_BUFFER, (m_grid + 2) * (m_grid + 2) * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    m_solver->solve(temp, m_quantity[m_currentContext], m_quantity[m_currentContext ^ 1], diffusionForNearbyGrid,
                    (1 + 4 * diffusionForNearbyGrid), m_grid);
    glBindBuffer(GL_COPY_READ_BUFFER, temp);
    glBindBuffer(GL_COPY_WRITE_BUFFER, m_quantity[m_currentContext]);
    glBufferData(GL_COPY_WRITE_BUFFER, (m_grid + 2) * (m_grid + 2) * sizeof(float), nullptr, GL_STATIC_DRAW);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, (m_grid + 2) * (m_grid + 2) * sizeof(float));
    glMemoryBarrier(GL_SHADER_STORAGE_BUFFER);
    glDeleteBuffers(1, &temp);
}

void Density::advect(float dt, uint32_t u, uint32_t v) {
    m_shaderUtility->ADVECT_DENSITY_PROGRAM.bind();
    m_shaderUtility->ADVECT_DENSITY_PROGRAM.bindBuffer(m_quantity[m_currentContext], 0);
    m_shaderUtility->ADVECT_DENSITY_PROGRAM.bindBuffer(m_quantity[m_currentContext ^ 1], 1);
    m_shaderUtility->ADVECT_DENSITY_PROGRAM.bindBuffer(u, 2);
    m_shaderUtility->ADVECT_DENSITY_PROGRAM.bindBuffer(v, 3);
    m_shaderUtility->ADVECT_DENSITY_PROGRAM.uniform1f("dt0", dt * m_grid);
    m_shaderUtility->ADVECT_DENSITY_PROGRAM.dispatch(m_grid, m_grid, 1);

    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bind();
    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bindBuffer(m_quantity[m_currentContext], 0);
    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.dispatch(1, 1, 1);
}

void Density::process(float dt, float diffusion, uint32_t u, uint32_t v) {
    addQuantity(dt);

    m_currentContext ^= 1;
    diffuse(dt, diffusion);

    m_currentContext ^= 1;
    advect(dt, u, v);
}

float *Density::enableAndGetReadWriteQuantity(bool isPrevious) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_quantity[m_currentContext ^ isPrevious]);
    return (float *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, (m_grid + 2) * (m_grid + 2) * sizeof(float),
                                      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
}

const float *Density::enableAndGetReadQuantity(bool isPrevious) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_quantity[m_currentContext ^ isPrevious]);
    return (float *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, (m_grid + 2) * (m_grid + 2) * sizeof(float),
                                      GL_MAP_READ_BIT);
}

void Density::disableReadOrWriteQuantity(bool isPrevious) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_quantity[m_currentContext ^ isPrevious]);
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}
