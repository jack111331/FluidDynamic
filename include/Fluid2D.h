//
// Created by Edge on 2020/4/23.
//

#ifndef FLUIDDYNAMIC_FLUID2D_H
#define FLUIDDYNAMIC_FLUID2D_H

#include <stdint.h>
#include <vo/GLFWWindowInfo.h>
#include <Shader.h>
#include "Velocity.h"
#include "Density.h"

class Fluid2D {
public:
    virtual ~Fluid2D();

    void init(int gridSize, int solverTimestep);

    void input(GLFWWindowInfo *windowInfo, float force, float source);

    void changeGridPosition();

    void update(float dt, float diffusion, float viscosity);

    void display(bool mode);

    void addDrivingForce(float dt, float vf, float *state);

    void addBuoyancy(float dt, float alpha, float beta, float gravity);

    void addDensity(int gridWidth, float width, int (&initWindLocation)[2], float source);

    void addGaussianWindForce(int gridWidth, float width, double windDirection, int (&initWindLocation)[2]);

    void addVortexForce(int gridWidth, float width, float r, int (&initVortexLocation)[2]);

    void clear();

private:
    int m_gridSize;

    uint32_t *m_meshIndices;
    float *m_meshPosition;
    uint32_t *m_gridIndices;
    float *m_gridPosition;
    Shader *m_densityFieldShader, *m_velocityFieldShader;
    uint32_t m_meshVAO, m_positionVBO, m_colorVBO, m_indicesEBO;
    uint32_t m_velocityVAO, m_velocityPositionVBO, m_velocityIndicesEBO;

    Velocity *m_velocityField;
    Density *m_densityField;

    static const bool VELOCITY_FIELD_MODE = true;
    static const bool DENSITY_FIELD_MODE = false;
};


#endif //FLUIDDYNAMIC_FLUID2D_H
