#include "Density.h"
#include "Utility.h"
#include <iostream>

Density::Density(int N, Solver *solver) : NavierStokes(N, solver){
  for(int i = 0;i < 2;++i) {
    m_quantity[i] = new float[(N+2)*(N+2)];
    std::fill_n(m_quantity[i], (N+2)*(N+2), 0.0f);
  }
}

Density::Density(const Density &v) {
  m_grid = v.m_grid;
  m_solver = v.m_solver;
  m_currentContext = v.m_currentContext;

  for(int k = 0;k < 2;++k) {
    m_quantity[k] = new float[(N+2)*(N+2)];
    for(int i = 0;i < (N+2)*(N+2);++i) {
      m_quantity[k][i] = v.m_quantity[k][i];
    }
  }
}

Density::~Density() {
  for(int i = 0;i < 2;++i) {
    delete m_quantity[i];
  }
}

void Density::process(float dt, float diffusion, float *u, float *v) {
  addQuantity(dt, m_quantity[m_currentContext], m_quantity[m_currentContext^1]);

  m_currentContext ^= 1;
  diffuse(dt, diffusion, 0, m_quantity[m_currentContext], m_quantity[m_currentContext^1]);

  m_currentContext ^= 1;
  advect(dt, 0, u, v, m_quantity[m_currentContext], m_quantity[m_currentContext^1]);
}

float *Density::getQuantity() {
  return m_quantity[m_currentContext];
}

float *Density::getPrevQuantity() {
  return m_quantity[m_currentContext ^ 1];
}
