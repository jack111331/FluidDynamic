#include "NavierStokes.h"
#include "Utility.h"
#include <iostream>

NavierStokes::NavierStokes(int N, Solver *solver) : m_grid(N), m_currentContext(0){
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

void NavierStokes::advectDerivative(float dt, int boundary, float *u, float *v, float *quantityDerivative, float *prevQuantityDerivative) {
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
      quantityDerivative[indexOf(i, j, m_grid)] = linearInterpolate2D(
                                                            x-xl,
                                                            y-yl,
                                                            prevQuantityDerivative[indexOf(xl, yl, m_grid)],
                                                            prevQuantityDerivative[indexOf(xr, yl, m_grid)],
                                                            prevQuantityDerivative[indexOf(xl, yu, m_grid)],
                                                            prevQuantityDerivative[indexOf(xr, yu, m_grid)]
      );
      // TODO calculate dpx/duk, dpy/duk
      quantityDerivative[indexOf(i, j, m_grid)] += x * linearInterpolate2DDerivative(
                                                            x-xl,
                                                            prevQuantityDerivative[indexOf(xl, yl, m_grid)],
                                                            prevQuantityDerivative[indexOf(xr, yl, m_grid)],
                                                            prevQuantityDerivative[indexOf(xl, yu, m_grid)],
                                                            prevQuantityDerivative[indexOf(xr, yu, m_grid)]
      );

      quantityDerivative[indexOf(i, j, m_grid)] += y * linearInterpolate2DDerivative(
                                                            y-yl,
                                                            prevQuantityDerivative[indexOf(xl, yl, m_grid)],
                                                            prevQuantityDerivative[indexOf(xl, yu, m_grid)],
                                                            prevQuantityDerivative[indexOf(xr, yl, m_grid)],
                                                            prevQuantityDerivative[indexOf(xr, yu, m_grid)]
      );
    }
  }
  setBoundary(boundary, quantity, m_grid);
}
