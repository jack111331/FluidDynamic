//
// Created by Edge on 2020/7/14.
//

#include "VelocityDerivative.h"
#include "Control.h"

VelocityDerivative::VelocityDerivative(int N) : m_grid(N) {
    m_velocityDerivative = new Velocity(N);
    m_shaderUtility = ShaderUtility::getInstance();
}

VelocityDerivative::~VelocityDerivative() {
    delete m_velocityDerivative;
}

void VelocityDerivative::process(float dt, Velocity *velocity, const ControlForce &controlForce) {
//TODO
    addForceDerivative(controlForce);

    m_velocityDerivative->m_currentContext ^= 1;
    advectUDerivative(dt, velocity->getBufferId(Velocity::U_COMPONENT, true),
                      velocity->getBufferId(Velocity::V_COMPONENT, true));
    advectVDerivative(dt, velocity->getBufferId(Velocity::U_COMPONENT, true),
                      velocity->getBufferId(Velocity::V_COMPONENT, true));

    m_velocityDerivative->massConserve();
}

void VelocityDerivative::addForceDerivative(const ControlForce &controlForce) {
//TODO
// dont include vorticity confinement... too complicate currently, just control force

    gaussianWindForceList;
    std::vector<VortexForce> vortexForceList;
}

void VelocityDerivative::advectUDerivative(float dt, uint32_t prevU, uint32_t prevV) {
    m_shaderUtility->ADVECT_U_VELOCITY_DERIVATIVE_PROGRAM.bind();
    m_shaderUtility->ADVECT_U_VELOCITY_DERIVATIVE_PROGRAM.bindBuffer(m_velocityDerivative->getBufferId(Velocity::U_COMPONENT, false), 0);
    m_shaderUtility->ADVECT_U_VELOCITY_DERIVATIVE_PROGRAM.bindBuffer(m_velocityDerivative->getBufferId(Velocity::U_COMPONENT, true), 1);
    m_shaderUtility->ADVECT_U_VELOCITY_DERIVATIVE_PROGRAM.bindBuffer(prevU, 2);
    m_shaderUtility->ADVECT_U_VELOCITY_DERIVATIVE_PROGRAM.bindBuffer(prevV, 3);
    m_shaderUtility->ADVECT_U_VELOCITY_DERIVATIVE_PROGRAM.uniform1f("dt0", dt * m_grid);
    m_shaderUtility->ADVECT_U_VELOCITY_DERIVATIVE_PROGRAM.dispatch(m_grid - 1, m_grid, 1);

    m_shaderUtility->SET_U_VELOCITY_BOUND_PROGRAM.bind();
    m_shaderUtility->SET_U_VELOCITY_BOUND_PROGRAM.bindBuffer(m_velocityDerivative->getBufferId(Velocity::U_COMPONENT, false), 0);
    m_shaderUtility->SET_U_VELOCITY_BOUND_PROGRAM.dispatch(m_grid + 1, 1, 1);
}

void VelocityDerivative::advectVDerivative(float dt, uint32_t prevU, uint32_t prevV) {
    m_shaderUtility->ADVECT_V_VELOCITY_DERIVATIVE_PROGRAM.bind();
    m_shaderUtility->ADVECT_V_VELOCITY_DERIVATIVE_PROGRAM.bindBuffer(m_velocityDerivative->getBufferId(Velocity::V_COMPONENT, false), 0);
    m_shaderUtility->ADVECT_V_VELOCITY_DERIVATIVE_PROGRAM.bindBuffer(m_velocityDerivative->getBufferId(Velocity::V_COMPONENT, true), 1);
    m_shaderUtility->ADVECT_V_VELOCITY_DERIVATIVE_PROGRAM.bindBuffer(prevU, 2);
    m_shaderUtility->ADVECT_V_VELOCITY_DERIVATIVE_PROGRAM.bindBuffer(prevV, 3);
    m_shaderUtility->ADVECT_V_VELOCITY_DERIVATIVE_PROGRAM.uniform1f("dt0", dt * m_grid);
    m_shaderUtility->ADVECT_V_VELOCITY_DERIVATIVE_PROGRAM.dispatch(m_grid, m_grid - 1, 1);

    m_shaderUtility->SET_V_VELOCITY_BOUND_PROGRAM.bind();
    m_shaderUtility->SET_V_VELOCITY_BOUND_PROGRAM.bindBuffer(m_velocityDerivative->getBufferId(Velocity::V_COMPONENT, false), 0);
    m_shaderUtility->SET_V_VELOCITY_BOUND_PROGRAM.dispatch(m_grid + 1, 1, 1);
}