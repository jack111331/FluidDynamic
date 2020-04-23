//
// Created by Edge on 2020/4/23.
//

#ifndef FLUIDDYNAMIC_FLUID2D_H
#define FLUIDDYNAMIC_FLUID2D_H

#include <stdint.h>
#include "Velocity.h"
#include "Density.h"

class Fluid2D {
public:
    void init(int gridSize, int solverTimestep);

    void
    input(int windowX, int windowY, double mouseXpos, double mouseYpos, double &prevMouseXpos, double &prevMouseYpos,
          const bool *mouseAction, float force, float source);

    void update(float dt, float diffusion, float viscosity);

    void display(bool mode);

    void clear();

private:
    int m_gridSize;

    uint32_t *m_meshIndices;
    float *m_meshPosition;
    uint32_t *m_gridIndices;
    float *m_gridPosition;

    Velocity *m_velocityField;
    Density *m_densityField;
};


#endif //FLUIDDYNAMIC_FLUID2D_H
