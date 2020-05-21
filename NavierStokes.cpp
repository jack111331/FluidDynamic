#include "NavierStokes.h"
#include "Utility.h"
#include <iostream>

NavierStokes::NavierStokes(int N) : m_grid(N), m_currentContext(0) {
}

void NavierStokes::addQuantity(float dt, float *quantity, float *adder) {
    for (int i = 1; i <= m_grid; ++i) {
        for (int j = 1; j <= m_grid; ++j) {
            quantity[indexOf(i, j, m_grid)] += dt * adder[indexOf(i, j, m_grid)];
        }
    }
}

void NavierStokes::diffuse(float dt, float diffusion, int boundary, float *quantity, float *prevQuantity) {
    float diffusionForNearbyGrid = dt * diffusion * m_grid * m_grid;
//    m_solver->solve(quantity, prevQuantity, diffusionForNearbyGrid, (1 + 4 * diffusionForNearbyGrid), boundary, m_grid);
}

void NavierStokes::advect(float dt, int boundary, float *u, float *v, float *quantity, float *prevQuantity) {
    float dt0 = dt * m_grid;
    for (int i = 1; i <= m_grid; ++i) {
        for (int j = 1; j <= m_grid; ++j) {
            // reverse flow by vector field
            // use average staggered MAC grid velocity
            float x = j - dt0 * (u[indexOfVelocityU(i, j, m_grid)] + u[indexOfVelocityU(i, j - 1, m_grid)]) * 0.5f;
            float y = i - dt0 * (v[indexOfVelocityV(i, j, m_grid)] + v[indexOfVelocityV(i - 1, j, m_grid)]) * 0.5f;
            if (x < 0.5f) x = 0.5f; else if (x > m_grid + 0.5f) x = m_grid + 0.5f;
            if (y < 0.5f) y = 0.5f; else if (y > m_grid + 0.5f) y = m_grid + 0.5f;
            int xl = x, xr = xl + 1;
            int yl = y, yu = yl + 1;
            // Linear interpolate
            quantity[indexOf(i, j, m_grid)] = linearInterpolate2D(x - xl,
                                                                  y - yl,
                                                                  prevQuantity[indexOf(yl, xl, m_grid)],
                                                                  prevQuantity[indexOf(yl, xr, m_grid)],
                                                                  prevQuantity[indexOf(yu, xl, m_grid)],
                                                                  prevQuantity[indexOf(yu, xr, m_grid)]);
        }
    }
    setBoundary(boundary, quantity, m_grid);
}
