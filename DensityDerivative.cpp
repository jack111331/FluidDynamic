//
// Created by Edge on 2020/7/14.
//

#include "DensityDerivative.h"
DensityDerivative::DensityDerivative(int N) : m_grid(N) {
    m_densityDerivative = new Density(N);
    m_shaderUtility = ShaderUtility::getInstance();
}

DensityDerivative::~DensityDerivative() {
    delete m_densityDerivative;
}


void DensityDerivative::process(float dt, float diffusion, Density *density, uint32_t u, uint32_t v) {

    advectDerivative(dt, density->getBufferId(true), u, v);

    m_densityDerivative->m_currentContext ^= 1;
    m_densityDerivative->diffuse(dt, diffusion);

}

void DensityDerivative::advectDerivative(float dt, uint32_t prevDensity, uint32_t u, uint32_t v) {
    m_shaderUtility->ADVECT_DENSITY_DERIVATIVE_PROGRAM.bind();
    m_shaderUtility->ADVECT_DENSITY_DERIVATIVE_PROGRAM.bindBuffer(m_densityDerivative->getBufferId(false), 0);
    m_shaderUtility->ADVECT_DENSITY_DERIVATIVE_PROGRAM.bindBuffer(m_densityDerivative->getBufferId(true), 1);
    m_shaderUtility->ADVECT_DENSITY_DERIVATIVE_PROGRAM.bindBuffer(prevDensity, 2);
    m_shaderUtility->ADVECT_DENSITY_DERIVATIVE_PROGRAM.bindBuffer(u, 3);
    m_shaderUtility->ADVECT_DENSITY_DERIVATIVE_PROGRAM.bindBuffer(v, 4);
    m_shaderUtility->ADVECT_DENSITY_DERIVATIVE_PROGRAM.uniform1f("dt0", dt * m_grid);
    m_shaderUtility->ADVECT_DENSITY_DERIVATIVE_PROGRAM.dispatch(m_grid, m_grid, 1);

    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bind();
    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bindBuffer(m_densityDerivative->getBufferId(false), 0);
    m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.dispatch(1, 1, 1);

}