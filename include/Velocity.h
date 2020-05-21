#pragma once

#include "Quantity.h"
#include <cstdint>

class Velocity : public MultipleQuantity {
private:
    int m_grid;
    int m_currentContext;
    float *m_uQuantity[2];
    float *m_vQuantity[2];

    void addForce(float dt);

    void advectU(float dt, float *u, const float *prevU, const float *prevV);

    void advectV(float dt, float *v, const float *prevV, const float *prevU);

    float curl(int x, int y);

    float dVOverDX(int i, int j);

    float dUOverDY(int i, int j);

    void vorticityConfinement(float dt, float vorticity);

    void massConserve(float dt);

public:
    Velocity(int N);

    ~Velocity();

    void clear();

    void clearPrev();

    void process(float dt, float diffusion, float *u, float *v);

    float *getQuantity(int component) override;

    float *getPrevQuantity(int component) override;

    static const int U_COMPONENT = 1;
    static const int V_COMPONENT = 2;
};
