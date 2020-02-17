#include "NavierStokes.h"
#include "Utility.h"
#include <iostream>

NavierStokes::NavierStokes(int N, Solver *solver) : m_grid(N), m_currentContext(0), m_currentContextAdjoint(0) {
  m_solver = solver;
}

void NavierStokes::addQuantity(float dt, float *quantity, float *adder) {
  for(int i = 1;i <= m_grid;++i) {
    for(int j = 1;j <= m_grid;++j) {
      quantity[indexOf(i, j, m_grid)] += dt * adder[indexOf(i, j, m_grid)];
    }
  }
}

void NavierStokes::diffuse(float dt, float diffusion, int boundary, float *quantity, float *prevQuantity) {
  float diffusionForNearbyGrid = dt * diffusion * m_grid * m_grid;
  m_solver->solve(quantity, prevQuantity, diffusionForNearbyGrid, (1 + 4 * diffusionForNearbyGrid), boundary, m_grid);
}

void NavierStokes::advect(float dt, int boundary, float *u, float *v, float *quantity, float *prevQuantity) {
  pushHeap(prevQuantity);
  pushHeap(v);
  pushHeap(u);

  float dt0 = dt*m_grid;
  for(int i = 1;i <= m_grid;++i) {
    for(int j = 1;j <= m_grid;++j) {
      // reverse flow by vector field
      float x = i - dt0 * u[indexOf(i, j, m_grid)], y = j - dt0 * v[indexOf(i, j, m_grid)];
      if(x < 0.5f) x = 0.5f; else if(x > m_grid + 0.5f) x = m_grid+0.5f;
      if(y < 0.5f) y = 0.5f; else if(y > m_grid + 0.5f) y = m_grid+0.5f;
      int xl = x, xr = xl+1;
      int yl = y, yu = yl+1;
      // Linear interpolate
      quantity[indexOf(i, j, m_grid)] = linearInterpolate2D(x-xl,
                                                            y-yl,
                                                            prevQuantity[indexOf(xl, yl, m_grid)],
                                                            prevQuantity[indexOf(xr, yl, m_grid)],
                                                            prevQuantity[indexOf(xl, yu, m_grid)],
                                                            prevQuantity[indexOf(xr, yu, m_grid)]);
    }
  }
  setBoundary(boundary, quantity, m_grid);
}

void NavierStokes::pushHeap(const float *content) {
  float *copyContent = new float[(N+2)*(N+2)];
  for(int i = 0;i < (N+2)*(N+2);++i) {
    copyContent[i] = content[i];
  }
  heap.push_back(copyContent);
}
void NavierStokes::popHeap(float *content) {
  float *copyContent = heap[heap.size()-1];
  for(int i = 0;i < (N+2)*(N+2);++i) {
    content[i] = copyContent[i];
  }
  delete copyContent;
  heap.pop_back();
}

void NavierStokes::addQuantityAdjoint(float dt, float *quantityAdjoint, float *adderAdjoint) {
  for(int i = (m_grid+2) * (m_grid+2) - 1;i >= 0;--i) {
    adderAdjoint[i] += dt * quantityAdjoint[i];
  }
}

void NavierStokes::diffuseAdjoint(float dt, float diffusion, int boundary, float *quantityAdjoint, float *prevQuantityAdjoint) {
  float diffusionForNearbyGrid = dt * diffusion * m_grid * m_grid;
  solver->solveAdjoint(quantityAdjoint, prevQuantityAdjoint, diffusionForNearbyGrid, (1 + 4 * diffusionForNearbyGrid), boundary, m_grid);
}
void NavierStokes::advectAdjoint(float dt, int boundary, float *u, float *v, float *uAdjoint, float *vAdjoint, float *prevQuantity, float *quantityAdjoint, float *prevQuantityAdjoint) {
  // Restore content from advect()
  popHeap(u);
  popHeap(v);
  popHeap(prevQuantity);

  float x, y;
  float dt0 = dt * N;
  setBoundaryAdjoint(boundary, quantityAdjoint, m_grid);

  for(int j = m_grid;j >= 1;--j) {
    for(int i = m_grid;i >= 1;--i) {
      float x = i - dt0 * u[indexOf(i, j, m_grid)], y = j - dt0 * v[indexOf(i, j, m_grid)];
      if(x < 0.5f) {
        x = 0.5f;
      } else if(x > m_grid+0.5f) {
        x = m_grid+0.5f;
      }
      if(y < 0.5f) {
        y = 0.5f;
      } else if(y > m_grid+0.5f) {
        y = m_grid+0.5f;
      }
      int xl = x, xr = xl+1;
      int yl = y, yu = yl+1;
      float s0 = x-xl, s1 = 1-s0, t0 = y-yl, t1 = 1-t0;
      prevQuantityAdjoint[indexOf(xr, yu, m_grid)] += s1 * t1 * QuantityAdjoint[indexOf(i, j, m_grid)];
      prevQuantityAdjoint[indexOf(xr, yl, m_grid)] += s1 * t0 * QuantityAdjoint[indexOf(i, j, m_grid)];
      prevQuantityAdjoint[indexOf(xl, yu, m_grid)] += s0 * t1 * QuantityAdjoint[indexOf(i, j, m_grid)];
      prevQuantityAdjoint[indexOf(xl, yl, m_grid)] += s0 * t0 * QuantityAdjoint[indexOf(i, j, m_grid)];

      uAdjoint[indexOf(i, j)] += dt0 * (t0 * (prevQuantity[indexOf(xl, yl, m_grid)] - prevQuantity[indexOf(xr, yl, m_grid)]) + t1 * (prevQuantity[indexOf(xl, yu, m_grid)] - prevQuantity[indexOf(xr, yu, m_grid)]));
      vAdjoint[indexOf(i, j)] += dt0 * (s0 * (prevQuantity[indexOf(xl, yl, m_grid)] - prevQuantity[indexOf(xl, yu, m_grid)]) + s1 * (prevQuantity[indexOf(xr, yl, m_grid)] - prevQuantity[indexOf(xr, yu, m_grid)]));

      quantityAdjoint[indexOf(i, j)] = 0.0f;
    }
  }
}
