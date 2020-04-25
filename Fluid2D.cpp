//
// Created by Edge on 2020/4/23.
//

#include <cmath>
#include <algorithm>
#include <Utility.h>
#include <GL/glew.h>
#include "Fluid2D.h"

using std::max;
using std::min;

Fluid2D::~Fluid2D() {
    delete m_meshPosition;
    delete m_meshIndices;
    delete m_gridPosition;
    delete m_gridIndices;

    delete m_densityFieldShader;
    delete m_velocityFieldShader;

    delete m_velocityField;
    delete m_densityField;
}

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

    // mesh shader init
    m_densityFieldShader = new Shader();
    m_densityFieldShader->CreateShader("resources/shader/mesh.vs", "resources/shader/mesh.fs");

    // velocity shader init
    m_velocityFieldShader = new Shader();
    m_velocityFieldShader->CreateShader("resources/shader/velocity.vs", "resources/shader/velocity.fs");

    // Mesh VAO
    glGenVertexArrays(1, &m_meshVAO);
    glBindVertexArray(m_meshVAO);

    // Mesh VBO
    glGenBuffers(1, &m_positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_positionVBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * (gridSize + 2) * (gridSize + 2) * sizeof(float), m_meshPosition, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Color VBO
    glGenBuffers(1, &m_colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
    glBufferData(GL_ARRAY_BUFFER, (gridSize + 2) * (gridSize + 2) * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    // Mesh EBO
    glGenBuffers(1, &m_indicesEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * (gridSize + 1) * (gridSize + 1) * sizeof(uint32_t), m_meshIndices,
                 GL_STATIC_DRAW);


    // Velocity VAO
    glGenVertexArrays(1, &m_velocityVAO);
    glBindVertexArray(m_velocityVAO);

    // Velocity VBO
    glGenBuffers(1, &m_velocityPositionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_velocityPositionVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 3 * gridSize * gridSize * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * gridSize * gridSize * sizeof(float), m_gridPosition);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // EBO
    glGenBuffers(1, &m_velocityIndicesEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_velocityIndicesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * gridSize * gridSize * sizeof(uint32_t), m_gridIndices, GL_STATIC_DRAW);


    // Navier Stokes Field Attribute
    m_densityField = new Density(gridSize, new GaussSeidelSolver(solverTimestep));
    m_velocityField = new Velocity(gridSize);

}

void Fluid2D::input(GLFWWindowInfo *windowInfo, float force, float source) {
    // Process density and velocity field
    m_densityField->clearPrev();
    m_velocityField->clearPrev();

    int i = (static_cast<double>(windowInfo->windowHeight - windowInfo->mouseYPos) /
             static_cast<double>(windowInfo->windowHeight )) * m_gridSize + 1;
    int j = (static_cast<double>(windowInfo->mouseXPos) / static_cast<double>(windowInfo->windowWidth)) * m_gridSize +
            1;
    if (i >= 1 && i < m_gridSize && j >= 1 && j < m_gridSize) {
        float *density = m_densityField->getPrevQuantity();
        float *u = m_velocityField->getPrevQuantity(Velocity::U_COMPONENT);
        float *v = m_velocityField->getPrevQuantity(Velocity::V_COMPONENT);
        if (windowInfo->mouseAction[GLFWWindowInfo::MOUSE_LEFT]) {
            u[indexOfVelocityU(i, j, m_gridSize)] = force * (windowInfo->mouseXPos - windowInfo->prevMouseXPos);
            v[indexOfVelocityV(i, j, m_gridSize)] = force * (windowInfo->prevMouseYPos - windowInfo->mouseYPos);
        }
        if (windowInfo->mouseAction[GLFWWindowInfo::MOUSE_RIGHT]) {
            density[indexOf(i, j, m_gridSize)] = source;
        }
    }
    windowInfo->prevMouseXPos = windowInfo->mouseXPos;
    windowInfo->prevMouseYPos = windowInfo->mouseYPos;

}

void Fluid2D::changeGridPosition() {
    float *u = m_velocityField->getQuantity(Velocity::U_COMPONENT), *v = m_velocityField->getQuantity(
            Velocity::V_COMPONENT);
    float lengthPerGrid = 2.0f / m_gridSize;
    for (int i = 0; i < m_gridSize; ++i) {
        for (int j = 0; j < m_gridSize; ++j) {
            m_gridPosition[3 * (i * m_gridSize + j)] = -1.0f + lengthPerGrid * ((float) j + 0.5f) +
                                                       (u[indexOfVelocityU(i, j + 1, m_gridSize)] +
                                                        u[indexOfVelocityU(i, j, m_gridSize)]) * 0.5f;
            m_gridPosition[3 * (i * m_gridSize + j) + 1] = -1.0f + lengthPerGrid * ((float) i + 0.5f) +
                                                           (v[indexOfVelocityV(i + 1, j, m_gridSize)] +
                                                            v[indexOfVelocityV(i, j, m_gridSize)]) * 0.5f;
            m_gridPosition[3 * (i * m_gridSize + j) + 2] = 0.0f;
        }
    }
}

void Fluid2D::update(float dt, float diffusion, float viscosity) {
    // FIXME alpha and beta
//    addBuoyancy(dt, -0.000625, 5.0f, -9.81);
//    addBuoyancy(dt, -0.000625, 5.0f, 1);
    addBuoyancy(dt, 0.0f, 0.4f, -9.8);
    m_velocityField->process(dt, viscosity, nullptr, nullptr);
    m_densityField->process(dt, diffusion, m_velocityField->getQuantity(Velocity::U_COMPONENT),
                            m_velocityField->getQuantity(Velocity::V_COMPONENT));
}

void Fluid2D::display(bool mode) {
    if (mode == DENSITY_FIELD_MODE) {
        // Prepare density
        m_densityFieldShader->Use();
        glBindVertexArray(m_meshVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (m_gridSize + 2) * (m_gridSize + 2) * sizeof(float),
                        m_densityField->getQuantity());
        glDrawElements(GL_TRIANGLES, 6 * (m_gridSize + 1) * (m_gridSize + 1), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    } else if (mode == VELOCITY_FIELD_MODE) {
        // Prepare velocity
        m_velocityFieldShader->Use();
        glBindVertexArray(m_velocityVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_velocityPositionVBO);
        changeGridPosition();
        glBufferSubData(GL_ARRAY_BUFFER, 3 * m_gridSize * m_gridSize * sizeof(float),
                        3 * m_gridSize * m_gridSize * sizeof(float), m_gridPosition);
        glDrawElements(GL_LINES, 2 * m_gridSize * m_gridSize, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void Fluid2D::addBuoyancy(float dt, float alpha, float beta, float gravity) {
    // FIXME local large buoyancy
    float *density = m_densityField->getQuantity();
    float *v = m_velocityField->getPrevQuantity(Velocity::V_COMPONENT);
    for (int i = 1; i <= m_gridSize; ++i) {
        for (int j = 1; j <= m_gridSize + 1; ++j) {
            float averageTemperature =
                    (density[indexOf(i + 1, j, m_gridSize)] + density[indexOf(i - 1, j, m_gridSize)] +
                     density[indexOf(i, j + 1, m_gridSize)] + density[indexOf(i, j - 1, m_gridSize)]) * 0.25f;
            v[indexOfVelocityV(i, j, m_gridSize)] += ((alpha * density[indexOf(i, j, m_gridSize)] -
                                                       beta *
                                                       (density[indexOf(i, j, m_gridSize)] - averageTemperature)) *
                                                      gravity) * dt;
        }
    }
}

void Fluid2D::addDensity(int gridWidth, float width, int (&initWindLocation)[2], float source) {
    float *density = m_densityField->getPrevQuantity();
    for (int i = max(initWindLocation[0] - gridWidth, 1);
         i <= min(initWindLocation[0] + gridWidth, m_gridSize); ++i) {
        for (int j = max(initWindLocation[1] - gridWidth, 1);
             j <= min(initWindLocation[1] + gridWidth, m_gridSize); ++j) {
            int deltaC[2] = {initWindLocation[0] - i, initWindLocation[1] - j};
            double gaussFalloff = exp(-width * (deltaC[0] * deltaC[0] + deltaC[1] * deltaC[1]));
            density[indexOf(j, i, m_gridSize)] += gaussFalloff * source;
        }
    }
}

void Fluid2D::addGaussianWindForce(int gridWidth, float width, double windDirection, int (&initWindLocation)[2]) {
    float *u = m_velocityField->getPrevQuantity(Velocity::U_COMPONENT);
    float *v = m_velocityField->getPrevQuantity(Velocity::V_COMPONENT);

    double uDirection = cos(windDirection), vDirection = sin(windDirection);
    for (int i = max(initWindLocation[0] - gridWidth, 1);
         i <= min(initWindLocation[0] + gridWidth, m_gridSize); ++i) {
        for (int j = max(initWindLocation[1] - gridWidth, 1);
             j <= min(initWindLocation[1] + gridWidth, m_gridSize); ++j) {
            int deltaC[2] = {initWindLocation[0] - i, initWindLocation[1] - j};
            double gaussFalloff = exp(-width * (deltaC[0] * deltaC[0] + deltaC[1] * deltaC[1]));
            u[indexOfVelocityU(j, i, m_gridSize)] += gaussFalloff * uDirection;
            v[indexOfVelocityV(j, i, m_gridSize)] += gaussFalloff * vDirection;
        }
    }
}

void Fluid2D::addVortexForce(int gridWidth, float width, float r, int (&initVortexLocation)[2]) {
    float *u = m_velocityField->getPrevQuantity(Velocity::U_COMPONENT);
    float *v = m_velocityField->getPrevQuantity(Velocity::V_COMPONENT);

    for (int i = max(initVortexLocation[0] - gridWidth, 1);
         i <= min(initVortexLocation[0] + gridWidth, m_gridSize); ++i) {
        for (int j = max(initVortexLocation[1] - gridWidth, 1);
             j <= min(initVortexLocation[1] + gridWidth, m_gridSize); ++j) {
            int deltaC[2] = {initVortexLocation[0] - i, initVortexLocation[1] - j};
            float uDirection = -deltaC[1], vDirection = deltaC[0];
            double gaussFalloff = exp(-width * (deltaC[0] * deltaC[0] + deltaC[1] * deltaC[1]));
            u[indexOfVelocityU(j, i, m_gridSize)] += r * gaussFalloff * uDirection;
            v[indexOfVelocityV(j, i, m_gridSize)] += r * gaussFalloff * vDirection;
        }
    }

}

void Fluid2D::clear() {
    m_densityField->clear();
}
