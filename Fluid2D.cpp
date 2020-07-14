//
// Created by Edge on 2020/4/23.
//

#include <cmath>
#include <algorithm>
#include <Utility.h>
#include <GL/glew.h>
#include "Fluid2D.h"
#include <iostream>

using std::max;
using std::min;

Fluid2D::~Fluid2D() {
    delete[] m_meshPosition;
    delete[] m_meshIndices;
    delete[] m_gridPosition;
    delete[] m_gridIndices;

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
    m_meshTexCoord = new float[2 * (gridSize + 2) * (gridSize + 2)];
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

    float lengthPerGridDensity = 2.0f / (gridSize + 1);
    for (int i = 0; i <= gridSize + 1; ++i) {
        for (int j = 0; j <= gridSize + 1; ++j) {
            m_meshPosition[3 * indexOf(i, j, gridSize)] = -1.0f + lengthPerGridDensity * j;
            m_meshPosition[3 * indexOf(i, j, gridSize) + 1] = -1.0f + lengthPerGridDensity * i;
            m_meshPosition[3 * indexOf(i, j, gridSize) + 2] = 0.0f;

            m_meshTexCoord[2 * indexOf(i, j, gridSize)] = lengthPerGridDensity * j / 2.0;
            m_meshTexCoord[2 * indexOf(i, j, gridSize) + 1] = lengthPerGridDensity * i / 2.0;
        }
    }

    int offset = gridSize * gridSize;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            m_gridIndices[2 * (i * gridSize + j)] = (i * gridSize + j);
            m_gridIndices[2 * (i * gridSize + j) + 1] = (i * gridSize + j) + offset;
        }
    }

    float lengthPerGridVelocity = 2.0f / gridSize;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            m_gridPosition[3 * (i * gridSize + j)] = -1.0f + lengthPerGridVelocity * ((float) j + 0.5f);
            m_gridPosition[3 * (i * gridSize + j) + 1] = -1.0f + lengthPerGridVelocity * ((float) i + 0.5f);
            m_gridPosition[3 * (i * gridSize + j) + 2] = 0.0f;
        }
    }

    // mesh shader init
    m_densityFieldShader = new Shader("resources/shader/mesh.vs", "resources/shader/mesh.fs");
    m_densityFieldShader->buildShader();

    // velocity shader init
    m_velocityFieldShader = new Shader("resources/shader/velocity.vs", "resources/shader/velocity.fs");
    m_velocityFieldShader->buildShader();

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

    // Tex Coord VBO
    glGenBuffers(1, &m_texCoordVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * (gridSize + 2) * (gridSize + 2) * sizeof(float), m_meshTexCoord, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(2);

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
    m_densityField = new Density(gridSize);
    m_velocityField = new Velocity(gridSize);

}

void Fluid2D::input(float force, float source) {
    // Process density and velocity field
    m_densityField->clear(true);
    m_velocityField->clear(true);

    GLFWWindowInfo *glfwWindowInfo = GLFWWindowInfo::getInstance();

    int i = (static_cast<double>(glfwWindowInfo->windowHeight - glfwWindowInfo->mouseYPos) /
             static_cast<double>(glfwWindowInfo->windowHeight )) * m_gridSize + 1;
    int j = (static_cast<double>(glfwWindowInfo->mouseXPos) / static_cast<double>(glfwWindowInfo->windowWidth)) * m_gridSize +
            1;
    if (i >= 1 && i < m_gridSize && j >= 1 && j < m_gridSize) {
        float *density = m_densityField->enableAndGetReadWriteQuantity(true);
        float *u = m_velocityField->enableAndGetReadWriteQuantity(Velocity::U_COMPONENT, true);
        float *v = m_velocityField->enableAndGetReadWriteQuantity(Velocity::V_COMPONENT, true);
        if (glfwWindowInfo->mouseAction[GLFWWindowInfo::MOUSE_LEFT]) {
            u[indexOfVelocityU(i, j, m_gridSize)] = force * (glfwWindowInfo->mouseXPos - glfwWindowInfo->prevMouseXPos);
            v[indexOfVelocityV(i, j, m_gridSize)] = force * (glfwWindowInfo->prevMouseYPos - glfwWindowInfo->mouseYPos);
        }
        if (glfwWindowInfo->mouseAction[GLFWWindowInfo::MOUSE_RIGHT]) {
            density[indexOf(i, j, m_gridSize)] = source;
        }
        m_densityField->disableReadOrWriteQuantity(true);
        m_velocityField->disableReadOrWriteQuantity(Velocity::U_COMPONENT, true);
        m_velocityField->disableReadOrWriteQuantity(Velocity::V_COMPONENT, true);
    }
    glfwWindowInfo->prevMouseXPos = glfwWindowInfo->mouseXPos;
    glfwWindowInfo->prevMouseYPos = glfwWindowInfo->mouseYPos;

}

void Fluid2D::changeGridPosition() {
    const float *u = m_velocityField->enableAndGetReadQuantity(Velocity::U_COMPONENT, false);
    const float *v = m_velocityField->enableAndGetReadQuantity(Velocity::V_COMPONENT, false);
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
    m_velocityField->disableReadOrWriteQuantity(Velocity::U_COMPONENT, false);
    m_velocityField->disableReadOrWriteQuantity(Velocity::V_COMPONENT, false);
}

void Fluid2D::update(float dt, float diffusion, float viscosity) {
    // FIXME alpha and beta
//    addBuoyancy(dt, -0.000625, 5.0f, -9.81);
//    addBuoyancy(dt, -0.000625, 5.0f, 1);
    addBuoyancy(dt, -0.1f, 0.3f, -9.8);
    m_velocityField->process(dt, viscosity);
    m_densityField->process(dt, diffusion, m_velocityField->getBufferId(Velocity::U_COMPONENT, false),
                            m_velocityField->getBufferId(Velocity::V_COMPONENT, false));
    for (auto environment : m_environmentList) {
        environment->advect(dt, m_gridSize, m_meshVAO, m_velocityField->getTextureId());
    }
}

void Fluid2D::display(int mode) {
    if (mode == DENSITY_FIELD_MODE) {
        // Prepare density
        const float *density = m_densityField->enableAndGetReadQuantity(false);
        m_densityFieldShader->bind();
        glBindVertexArray(m_meshVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (m_gridSize + 2) * (m_gridSize + 2) * sizeof(float), density);
        glDrawElements(GL_TRIANGLES, 6 * (m_gridSize + 1) * (m_gridSize + 1), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        m_densityField->disableReadOrWriteQuantity(false);
    } else if (mode == VELOCITY_FIELD_MODE) {
        // Prepare velocity
        m_velocityFieldShader->bind();
        glBindVertexArray(m_velocityVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_velocityPositionVBO);
        changeGridPosition();
        glBufferSubData(GL_ARRAY_BUFFER, 3 * m_gridSize * m_gridSize * sizeof(float),
                        3 * m_gridSize * m_gridSize * sizeof(float), m_gridPosition);
        glDrawElements(GL_LINES, 2 * m_gridSize * m_gridSize, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    } else if (mode == TEXTURE_MODE) {
        for (auto & i : m_environmentList) {
            i->drawEnvironment();
        }
    }
}

void Fluid2D::addDrivingForce(float dt, float vf, float *state) {
    // blur current density
    const float *density = m_densityField->enableAndGetReadWriteQuantity(false);

    float *bluredDensity = new float[(m_gridSize + 2) * (m_gridSize + 2)];
    float *bluredState = new float[(m_gridSize + 2) * (m_gridSize + 2)];
    Density::blur(density, m_gridSize, 1, bluredDensity);
    Density::blur(state, m_gridSize, 1, bluredState);
    setBoundary(0, bluredDensity, m_gridSize);
    setBoundary(0, bluredState, m_gridSize);
    for (int i = 1; i <= m_gridSize; ++i) {
        for (int j = 1; j <= m_gridSize; ++j) {
            std::cout << dt * vf
                         * ((bluredDensity[indexOf(i, j + 1, m_gridSize)] +
                             bluredDensity[indexOf(i, j, m_gridSize)]) * 0.5f)
                         * ((bluredState[indexOf(i, j + 1, m_gridSize)] -
                             bluredState[indexOf(i, j, m_gridSize)]) / m_gridSize)
                         / ((bluredState[indexOf(i, j + 1, m_gridSize)] +
                             bluredState[indexOf(i, j, m_gridSize)]) * 0.5f + 1e-10) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "----" << std::endl;
    getchar();
    float *u = m_velocityField->enableAndGetReadWriteQuantity(Velocity::U_COMPONENT, true);
    float *v = m_velocityField->enableAndGetReadWriteQuantity(Velocity::V_COMPONENT, true);

    for (int i = 1; i <= m_gridSize; ++i) {
        for (int j = 1; j <= m_gridSize; ++j) {
            // TODO when target state and current state is equal, make sure dont do divide and multiply
            double force[2] = {
                    dt * vf
                    * ((bluredDensity[indexOf(i, j + 1, m_gridSize)] +
                        bluredDensity[indexOf(i, j, m_gridSize)]) * 0.5f)
                    * ((bluredState[indexOf(i, j + 1, m_gridSize)] -
                        bluredState[indexOf(i, j, m_gridSize)]) / m_gridSize)
                    / ((bluredState[indexOf(i, j + 1, m_gridSize)] +
                        bluredState[indexOf(i, j, m_gridSize)]) * 0.5f + 1e-10),

                    dt * vf
                    * ((bluredDensity[indexOf(i + 1, j, m_gridSize)] +
                        bluredDensity[indexOf(i, j, m_gridSize)]) * 0.5f)
                    * ((bluredState[indexOf(i + 1, j, m_gridSize)] -
                        bluredState[indexOf(i, j, m_gridSize)]) / m_gridSize)
                    / ((bluredState[indexOf(i + 1, j, m_gridSize)] +
                        bluredState[indexOf(i, j, m_gridSize)]) * 0.5f + 1e-10)
            };
            u[indexOfVelocityU(i, j, m_gridSize)] += force[0];
            v[indexOfVelocityV(i, j, m_gridSize)] += force[1];
        }
    }
    m_densityField->disableReadOrWriteQuantity(false);
    m_velocityField->disableReadOrWriteQuantity(Velocity::U_COMPONENT, true);
    m_velocityField->disableReadOrWriteQuantity(Velocity::V_COMPONENT, true);
    delete[] bluredDensity;
    delete[] bluredState;
}

void Fluid2D::addBuoyancy(float dt, float alpha, float beta, float gravity) {
    // FIXME local large buoyancy
    const float *density = m_densityField->enableAndGetReadQuantity(false);
    float *v = m_velocityField->enableAndGetReadWriteQuantity(Velocity::V_COMPONENT, true);
    for (int i = 1; i <= m_gridSize; ++i) {
        for (int j = 1; j <= m_gridSize + 1; ++j) {
            float averageTemperature =
                    (density[indexOf(i + 1, j, m_gridSize)] + density[indexOf(i - 1, j, m_gridSize)] +
                     density[indexOf(i, j + 1, m_gridSize)] + density[indexOf(i, j - 1, m_gridSize)]) * 0.25f;
            v[indexOfVelocityV(i, j, m_gridSize)] += (alpha * density[indexOf(i, j, m_gridSize)]
                                                      - beta
                                                        * (density[indexOf(i, j, m_gridSize)] - averageTemperature))
                                                     * gravity * dt;
        }
    }
    m_densityField->disableReadOrWriteQuantity(false);
    m_velocityField->disableReadOrWriteQuantity(Velocity::V_COMPONENT, true);
}

void Fluid2D::addDensity(int gridWidth, float width, int (&initWindLocation)[2], float source) {
    float *density = m_densityField->enableAndGetReadWriteQuantity(true);
    for (int i = max(initWindLocation[0] - gridWidth, 1);
         i <= min(initWindLocation[0] + gridWidth, m_gridSize); ++i) {
        for (int j = max(initWindLocation[1] - gridWidth, 1);
             j <= min(initWindLocation[1] + gridWidth, m_gridSize); ++j) {
            int deltaC[2] = {initWindLocation[0] - i, initWindLocation[1] - j};
            double gaussFalloff = exp(-width * (deltaC[0] * deltaC[0] + deltaC[1] * deltaC[1]));
            density[indexOf(j, i, m_gridSize)] += gaussFalloff * source;
        }
    }
    m_densityField->disableReadOrWriteQuantity(true);
}

void Fluid2D::addGaussianWindForce(int gridWidth, float width, double windDirection, int (&initWindLocation)[2]) {
    float *u = m_velocityField->enableAndGetReadWriteQuantity(Velocity::U_COMPONENT, true);
    float *v = m_velocityField->enableAndGetReadWriteQuantity(Velocity::V_COMPONENT, true);

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
    m_velocityField->disableReadOrWriteQuantity(Velocity::U_COMPONENT, true);
    m_velocityField->disableReadOrWriteQuantity(Velocity::V_COMPONENT, true);
}

void Fluid2D::addVortexForce(int gridWidth, float width, float r, int (&initVortexLocation)[2]) {
    float *u = m_velocityField->enableAndGetReadWriteQuantity(Velocity::U_COMPONENT, true);
    float *v = m_velocityField->enableAndGetReadWriteQuantity(Velocity::V_COMPONENT, true);

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
    m_velocityField->disableReadOrWriteQuantity(Velocity::U_COMPONENT, true);
    m_velocityField->disableReadOrWriteQuantity(Velocity::V_COMPONENT, true);

}

void Fluid2D::addEnvironment(Environment *environment) {
    m_environmentList.push_back(environment);
}


void Fluid2D::clear() {
    m_densityField->clear(false);
    m_densityField->clear(true);
    m_velocityField->clear(false);
    m_velocityField->clear(true);
}
