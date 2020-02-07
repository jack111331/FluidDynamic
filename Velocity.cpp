#include "Velocity.h"
#include "Utility.h"
#include <iostream>

Velocity::Velocity(int N, Solver *solver) : NavierStokes(N, solver){
  for(int i = 0;i < 2;++i) {
    m_uQuantity[i] = new float[(N+2)*(N+2)];
    m_vQuantity[i] = new float[(N+2)*(N+2)];
    std::fill_n(m_uQuantity[i], (N+2)*(N+2), 0.0f);
    std::fill_n(m_vQuantity[i], (N+2)*(N+2), 0.0f);
  }
}

Velocity::~Velocity() {
  for(int i = 0;i < 2;++i) {
    delete m_uQuantity[i];
    delete m_vQuantity[i];
  }
}

void Velocity::process(float dt, float diffusion, float *u, float *v) {
  addQuantity(dt, m_uQuantity[m_currentContext], m_uQuantity[m_currentContext^1]);
  addQuantity(dt, m_vQuantity[m_currentContext], m_vQuantity[m_currentContext^1]);

  m_currentContext ^= 1;
  diffuse(dt, diffusion, 1, m_uQuantity[m_currentContext], m_uQuantity[m_currentContext^1]);
  diffuse(dt, diffusion, 2, m_vQuantity[m_currentContext], m_vQuantity[m_currentContext^1]);

  // Satisfy the incompressible condition
  project(m_uQuantity[m_currentContext], m_vQuantity[m_currentContext], m_uQuantity[m_currentContext^1], m_vQuantity[m_currentContext^1]);

  m_currentContext ^= 1;
  advect(dt, 1, m_uQuantity[m_currentContext^1], m_vQuantity[m_currentContext^1], m_uQuantity[m_currentContext], m_uQuantity[m_currentContext^1]);
  advect(dt, 2, m_uQuantity[m_currentContext^1], m_vQuantity[m_currentContext^1], m_vQuantity[m_currentContext], m_vQuantity[m_currentContext^1]);
  project(m_uQuantity[m_currentContext], m_vQuantity[m_currentContext], m_uQuantity[m_currentContext^1], m_vQuantity[m_currentContext^1]);
}
void Velocity::project(float *u, float *v, float *p, float *div) {
  for(int i = 1;i <= m_grid;++i) {
    for(int j = 1;j <= m_grid;++j) {
      div[indexOf(i, j, m_grid)] = -0.5f * (u[indexOf(i+1, j, m_grid)] - u[indexOf(i-1, j, m_grid)] + v[indexOf(i, j+1, m_grid)] - v[indexOf(i, j-1, m_grid)]) / m_grid;
      p[indexOf(i, j, m_grid)] = 0.0f;
    }
  }
  setBoundary(0, div, m_grid);
  setBoundary(0, p, m_grid);

  // Solve gradient field
  m_solver->solve(p, div, 1, 4, 0, m_grid);

  for(int i = 1;i <= m_grid;++i) {
    for(int j = 1;j <= m_grid;++j) {
      u[indexOf(i, j, m_grid)] -= 0.5f * m_grid * (p[indexOf(i+1, j, m_grid)] - p[indexOf(i-1, j, m_grid)]);
      v[indexOf(i, j, m_grid)] -= 0.5f * m_grid * (p[indexOf(i, j+1, m_grid)] - p[indexOf(i, j-1, m_grid)]);
    }
  }
  setBoundary(1, m_uQuantity[m_currentContext], m_grid);
  setBoundary(2, m_vQuantity[m_currentContext], m_grid);
}

float *Velocity::getQuantity(int component) {
  if(component == uComponent) {
    return m_uQuantity[m_currentContext];
  } else if(component == vComponent) {
    return m_vQuantity[m_currentContext];
  } else {
    return nullptr;
  }
}
float *Velocity::getPrevQuantity(int component) {
  if(component == uComponent) {
    return m_uQuantity[m_currentContext ^ 1];
  } else if(component == vComponent) {
    return m_vQuantity[m_currentContext ^ 1];
  } else {
    return nullptr;
  }
}
