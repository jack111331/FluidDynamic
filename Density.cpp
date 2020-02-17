#include "Density.h"
#include "Utility.h"
#include <iostream>

Density::Density(int N, Solver *solver) : NavierStokes(N, solver){
  for(int i = 0;i < 2;++i) {
    m_quantity[i] = new float[(N+2)*(N+2)];
    m_quantityAdjoint[i] = new float[(N+2)*(N+2)];
    std::fill_n(m_quantity[i], (N+2)*(N+2), 0.0f);
    std::fill_n(m_quantityAdjoint[i], (N+2)*(N+2), 0.0f);
  }
}

Density::~Density() {
  for(int i = 0;i < 2;++i) {
    delete m_quantity[i];
    delete m_quantityAdjoint[i];
  }
}

void Density::process(float dt, float diffusion, float *u, float *v) {
  addQuantity(dt, m_quantity[m_currentContext], m_quantity[m_currentContext^1]);

  m_currentContext ^= 1;
  diffuse(dt, diffusion, 0, m_quantity[m_currentContext], m_quantity[m_currentContext^1]);

  m_currentContext ^= 1;
  advect(dt, 0, u, v, m_quantity[m_currentContext], m_quantity[m_currentContext^1]);
}

void Density::processAdjoint(float dt, float diffusion, float *u, float *v, float *uAdjoint, float *vAdjoint) {
  advectAdjoint(dt, 0, u, v, uAdjoint, vAdjoint, m_quantity[m_currentContext^1], m_quantityAdjoint[m_currentContextAdjoint], m_quantityAdjoint[m_currentContextAdjoint^1]);

  m_currentContextAdjoint ^= 1;

  diffuseAdjoint(dt, diffusion, 0, m_quantityAdjoint[m_currentContextAdjoint], m_quantityAdjoint[m_currentContextAdjoint^1]);

  m_currentContextAdjoint ^= 1;

  addQuantityAdjoint(dt, m_quantityAdjoint[m_currentContextAdjoint], m_quantityAdjoint[m_currentContextAdjoint^1]);
}

float *Density::getQuantity() {
  return m_quantity[m_currentContext];
}

float *Density::getPrevQuantity() {
  return m_quantity[m_currentContext ^ 1];
}
