#pragma once

#include "Solver.h"

class NavierStokes {
protected:
    int m_grid;
    int m_currentContext;

    void addQuantity(float dt, float *quantity, float *adder);

    void diffuse(float dt, float diffusion, int boundary, float *quantity, float *prevQuantity);

    void advect(float dt, int boundary, float *u, float *v, float *quantity, float *prevQuantity);

public:
    NavierStokes(int N);

    virtual void process(float dt, float diffusion, float *u, float *v) = 0;
};
