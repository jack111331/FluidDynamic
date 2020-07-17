//
// Created by Edge on 2020/7/14.
//

#ifndef FLUIDDYNAMIC_VELOCITYDERIVATIVE_H
#define FLUIDDYNAMIC_VELOCITYDERIVATIVE_H


#include "Velocity.h"

class ControlForce;

class VelocityDerivative {
public:
    VelocityDerivative(int N);

    ~VelocityDerivative();


    void process(float dt, Velocity *velocity, const ControlForce &controlForce);

    Velocity *m_velocityDerivative;
private:
    void addForceDerivative(const ControlForce &controlForce);
    void advectUDerivative(float dt, uint32_t prevU, uint32_t prevV);
    void advectVDerivative(float dt, uint32_t prevU, uint32_t prevV);

    int m_grid;

    ShaderUtility *m_shaderUtility;
};


#endif //FLUIDDYNAMIC_VELOCITYDERIVATIVE_H
