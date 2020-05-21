#include "Density.h"
#include "Utility.h"
#include <iostream>
#include <cmath>

Density::Density(int N, Solver *solver) : NavierStokes(N, solver) {
    for (int i = 0; i < 2; ++i) {
        m_quantity[i] = new float[(N + 2) * (N + 2)];
        std::fill_n(m_quantity[i], (N + 2) * (N + 2), 0.0f);
    }
}

Density::~Density() {
    for (int i = 0; i < 2; ++i) {
        delete[] m_quantity[i];
    }
    delete m_solver;
}

void Density::clear() {
    for (int i = 0; i < m_grid + 2; ++i) {
        for (int j = 0; j < m_grid + 2; ++j) {
            m_quantity[m_currentContext][indexOf(i, j, m_grid)] = 0.0f;
        }
    }
}

void Density::clearPrev() {
    for (int i = 0; i < m_grid + 2; ++i) {
        for (int j = 0; j < m_grid + 2; ++j) {
            m_quantity[m_currentContext ^ 1][indexOf(i, j, m_grid)] = 0.0f;
        }
    }
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

void Density::process(float dt, float diffusion, float *u, float *v) {
    addQuantity(dt, m_quantity[m_currentContext], m_quantity[m_currentContext ^ 1]);

    m_currentContext ^= 1;
    diffuse(dt, diffusion, 0, m_quantity[m_currentContext], m_quantity[m_currentContext ^ 1]);

    m_currentContext ^= 1;
    advect(dt, 0, u, v, m_quantity[m_currentContext], m_quantity[m_currentContext ^ 1]);
}

float *Density::getQuantity() {
    return m_quantity[m_currentContext];
}

float *Density::getPrevQuantity() {
    return m_quantity[m_currentContext ^ 1];
}
