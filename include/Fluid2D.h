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
#include "Environment.h"

class Fluid2D {
public:
    virtual ~Fluid2D();

    void init(int gridSize, int solverTimestep);

    void input(float force, float source);

    void changeGridPosition();

    void update(float dt, float diffusion, float viscosity);

    void display(int mode);

    void addDrivingForce(float dt, float vf, float *state);

    void addBuoyancy(float dt, float alpha, float beta, float gravity);

    void addDensity(int gridWidth, float width, int (&initWindLocation)[2], float source);

    void addGaussianWindForce(int gridWidth, float width, double windDirection, int (&initWindLocation)[2]);

    void addVortexForce(int gridWidth, float width, float r, int (&initVortexLocation)[2]);

    void addEnvironment(Environment *environment);

    void clear();

private:
    int m_gridSize;

    uint32_t *m_meshIndices;
    float *m_meshPosition;
    float *m_meshTexCoord;
    uint32_t *m_gridIndices;
    float *m_gridPosition;
    Shader *m_densityFieldShader, *m_velocityFieldShader;
    uint32_t m_meshVAO, m_positionVBO, m_colorVBO, m_texCoordVBO, m_indicesEBO;
    uint32_t m_velocityVAO, m_velocityPositionVBO, m_velocityIndicesEBO;

    Velocity *m_velocityField;
    Density *m_densityField;

    std::vector<Environment *> m_environmentList;

    static const int DENSITY_FIELD_MODE = 0;
    static const int VELOCITY_FIELD_MODE = 1;
    static const int TEXTURE_MODE = 2;
};


#endif //FLUIDDYNAMIC_FLUID2D_H
