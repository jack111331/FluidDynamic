//
// Created by Edge on 2020/7/14.
//

#ifndef FLUIDDYNAMIC_DENSITYDERIVATIVE_H
#define FLUIDDYNAMIC_DENSITYDERIVATIVE_H


#include "Density.h"

class DensityDerivative {
public:
    DensityDerivative(int N);

    ~DensityDerivative();


    void process(float dt, float diffusion, Density *density, uint32_t u, uint32_t v);

    Density *m_densityDerivative;
private:
    void advectDerivative(float dt, uint32_t prevDensity, uint32_t u, uint32_t v);

    int m_grid;

    ShaderUtility *m_shaderUtility;
};


#endif //FLUIDDYNAMIC_DENSITYDERIVATIVE_H
