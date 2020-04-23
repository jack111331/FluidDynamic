//
// Created by Edge on 2020/4/23.
//

#include <Utility.h>
#include "Fluid2D.h"

void Fluid2D::init(int gridSize, int solverTimestep) {
    this->m_gridSize = gridSize;

    // Display Related
    m_meshIndices = new uint32_t[6 * (gridSize + 1) * (gridSize + 1)];
    m_meshPosition = new float[3 * (gridSize + 2) * (gridSize + 2)];
    m_gridIndices = new uint32_t[2 * gridSize * gridSize];
    m_gridPosition = new float[3 * gridSize * gridSize];

    for (int i = 0; i < gridSize + 1; ++i) {
        for (int j = 0; j < gridSize + 1; ++j) {
            m_meshIndices[6 * (i * (gridSize + 1) + j)] = indexOf(i, j, gridSize);
            m_meshIndices[6 * (i * (gridSize + 1) + j) + 1] = indexOf(i + 1, j, gridSize);
            m_meshIndices[6 * (i * (gridSize + 1) + j) + 2] = indexOf(i + 1, j + 1, gridSize);
            m_meshIndices[6 * (i * (gridSize + 1) + j) + 3] = indexOf(i, j, gridSize);
            m_meshIndices[6 * (i * (gridSize + 1) + j) + 4] = indexOf(i + 1, j + 1, gridSize);
            m_meshIndices[6 * (i * (gridSize + 1) + j) + 5] = indexOf(i, j + 1, gridSize);
        }
    }

    float lengthPerGrid = 2.0f / (gridSize + 1);
    for (int i = 0; i <= gridSize + 1; ++i) {
        for (int j = 0; j <= gridSize + 1; ++j) {
            m_meshPosition[3 * indexOf(i, j, gridSize)] = -1.0f + lengthPerGrid * j;
            m_meshPosition[3 * indexOf(i, j, gridSize) + 1] = -1.0f + lengthPerGrid * i;
            m_meshPosition[3 * indexOf(i, j, gridSize) + 2] = 0.0f;
        }
    }

    int offset = gridSize * gridSize;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            m_gridIndices[2 * (i * gridSize + j)] = (i * gridSize + j);
            m_gridIndices[2 * (i * gridSize + j) + 1] = (i * gridSize + j) + offset;
        }
    }

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            m_gridPosition[3 * (i * gridSize + j)] = -1.0f + lengthPerGrid * ((float) j + 0.5f);
            m_gridPosition[3 * (i * gridSize + j) + 1] = -1.0f + lengthPerGrid * ((float) i + 0.5f);
            m_gridPosition[3 * (i * gridSize + j) + 2] = 0.0f;
        }
    }

    // Navier Stokes Field Attribute
    m_densityField = new Density(gridSize, new GaussSeidelSolver(solverTimestep));
    m_velocityField = new Velocity(gridSize);

}

void Fluid2D::input(int windowX, int windowY, double mouseXpos, double mouseYpos, double &prevMouseXpos,
                    double &prevMouseYpos, const bool *mouseAction, float force, float source) {
    // Process density and velocity field
    m_densityField->clearPrev();
    m_velocityField->clearPrev();

    int i = (static_cast<double>(windowY - mouseYpos) / static_cast<double>(windowY)) * m_gridSize + 1;
    int j = (static_cast<double>(mouseXpos) / static_cast<double>(windowX)) * m_gridSize + 1;
    if (i >= 1 && i < m_gridSize && j >= 1 && j < m_gridSize) {
        float *density = m_densityField->getPrevQuantity();
        float *u = m_velocityField->getPrevQuantity(Velocity::uComponent);
        float *v = m_velocityField->getPrevQuantity(Velocity::vComponent);
        if (mouseAction[0]) {
            u[indexOfVelocityU(i, j, m_gridSize)] = force * (mouseXpos - prevMouseXpos);
            u[indexOfVelocityU(i, j + 1, m_gridSize)] = force * (mouseXpos - prevMouseXpos);
            v[indexOfVelocityV(i, j, m_gridSize)] = force * (prevMouseYpos - mouseYpos);
            v[indexOfVelocityV(i + 1, j, m_gridSize)] = force * (prevMouseYpos - mouseYpos);
        }
        if (mouseAction[1]) {
            density[indexOf(i, j, m_gridSize)] = source;
        }
    }
    prevMouseXpos = mouseXpos;
    prevMouseYpos = mouseYpos;

}

void Fluid2D::update(float dt, float diffusion, float viscosity) {
    m_velocityField->process(dt, viscosity, nullptr, nullptr);
    m_densityField->process(dt, diffusion, m_velocityField->getQuantity(Velocity::uComponent),
                            m_velocityField->getQuantity(Velocity::vComponent));
}

void Fluid2D::display(bool mode) {

}

void Fluid2D::clear() {
}
