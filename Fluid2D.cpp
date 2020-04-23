//
// Created by Edge on 2020/4/23.
//

#include <Utility.h>
#include "Fluid2D.h"

void Fluid2D::init(int gridSize, int solverTimestep) {
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

void Fluid2D::update() {
    // Process density and velocity field
    m_DensityField->clearPrev();
    m_velocityField->clearPrev();
    float *prevU = m_velocityField->getPrevQuantity(Velocity::uComponent), *prevV = m_velocityField->getPrevQuantity(Velocity::vComponent);
    float *density = m_densityField->getPrevQuantity();
    for(int i = 0;i < N+2;++i) {
        for(int j = 0;j < N+2;++j) {
            density[indexOf(i, j, N)] = 0.0f;
        }
    }
    for(int i = 0;i <= N;++i) {
        for(int j = 0;j <= N+1;++j) {
            prevU[indexOfVelocityU(j, i, N)] = prevV[indexOfVelocityV(i, j, N)] = 0.0f;
        }
    }
    glfwPollEvents();
    mouseActionHandler();
    velocityField->process(dt, viscosity, u, v);
    float *prevU = m_velocityField->getPrevQuantity(Velocity::uComponent), *v = velocityField->getPrevQuantity(Velocity::vComponent);
    u = velocityField->getQuantity(Velocity::uComponent);
    v = velocityField->getQuantity(Velocity::vComponent);
    densityField->process(dt, diffusion, u, v);
    density = densityField->getQuantity();

}