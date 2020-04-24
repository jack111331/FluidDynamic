#include "Velocity.h"
#include "Utility.h"
#include "Solver.h"
#include <cmath>
#include <iostream>

using namespace std;

// #include <Eigen/Eigen>
// using namespace Eigen;
// #include <vector>

Velocity::Velocity(int N) : m_grid(N), m_currentContext(0) {
    for (int i = 0; i < 2; ++i) {
        // m_uQuantity[indexOfVelocityU(i, j, m_grid)] = u_(i, j-1/2)
        // m_vQuantity[indexOfVelocityV(i, j, m_grid)] = v_(i-1/2, j)

        // Extend upper and lower as boundary
        m_uQuantity[i] = new float[(N + 2) * (N + 1)];
        // Extend left and right as boundary
        m_vQuantity[i] = new float[(N + 1) * (N + 2)];
        std::fill_n(m_uQuantity[i], (N + 2) * (N + 1), 0.0f);
        std::fill_n(m_vQuantity[i], (N + 1) * (N + 2), 0.0f);
    }
}

Velocity::~Velocity() {
    for (int i = 0; i < 2; ++i) {
        delete m_uQuantity[i];
        delete m_vQuantity[i];
    }
}

void Velocity::clear() {
    for (int i = 0; i <= m_grid; ++i) {
        for (int j = 0; j <= m_grid + 1; ++j) {
            m_uQuantity[m_currentContext][indexOfVelocityU(j, i,
                                                           m_grid)] = m_vQuantity[m_currentContext][indexOfVelocityV(i,
                                                                                                                     j,
                                                                                                                     m_grid)] = 0.0f;
        }
    }
}

void Velocity::clearPrev() {
    for (int i = 0; i <= m_grid; ++i) {
        for (int j = 0; j <= m_grid + 1; ++j) {
            m_uQuantity[m_currentContext ^ 1][indexOfVelocityU(j, i, m_grid)] = m_vQuantity[m_currentContext ^
                                                                                            1][indexOfVelocityV(i, j,
                                                                                                                m_grid)] = 0.0f;
        }
    }
}

void Velocity::addForce(float dt) {
    for (int i = 1; i <= m_grid; ++i) {
        for (int j = 1; j <= m_grid - 1; ++j) {
            m_uQuantity[m_currentContext][indexOfVelocityU(i, j, m_grid)] +=
                    dt * m_uQuantity[m_currentContext ^ 1][indexOfVelocityU(i, j, m_grid)];
        }
    }
    setUBoundary(m_uQuantity[m_currentContext], m_grid);

    for (int i = 1; i <= m_grid - 1; ++i) {
        for (int j = 1; j <= m_grid; ++j) {
            m_vQuantity[m_currentContext][indexOfVelocityV(i, j, m_grid)] +=
                    dt * m_vQuantity[m_currentContext ^ 1][indexOfVelocityV(i, j, m_grid)];
        }
    }
    setVBoundary(m_vQuantity[m_currentContext], m_grid);
}

void Velocity::advectU(float dt, float *u, const float *prevU, const float *prevV) {
    float dt0 = dt * m_grid;
    for (int i = 1; i <= m_grid; ++i) {
        for (int j = 1; j <= m_grid - 1; ++j) {
            // reverse flow by velocity field
            // use average staggered MAC grid velocity
            float x = j - dt0 * prevU[indexOfVelocityU(i, j, m_grid)];
            float y =
                    i - dt0 * 0.25f * (prevV[indexOfVelocityV(i - 1, j, m_grid)] + prevV[indexOfVelocityV(i, j, m_grid)]
                                       + prevV[indexOfVelocityV(i - 1, j + 1, m_grid)] +
                                       prevV[indexOfVelocityV(i, j + 1, m_grid)]);
            if (x < 0.0f) x = 0.0f; else if (x > m_grid) x = m_grid;
            if (y < 0.5f) y = 0.5f; else if (y > m_grid + 0.5f) y = m_grid + 0.5f;
            int xl = x, xr = xl + 1;
            int yl = y, yu = yl + 1;
            // Linear interpolate
            u[indexOfVelocityU(i, j, m_grid)] = linearInterpolate2D(
                    x - xl,
                    y - yl,
                    prevU[indexOfVelocityU(yl, xl, m_grid)],
                    prevU[indexOfVelocityU(yl, xr, m_grid)],
                    prevU[indexOfVelocityU(yu, xl, m_grid)],
                    prevU[indexOfVelocityU(yu, xr, m_grid)]
            );
        }
    }
    setUBoundary(u, m_grid);
}

void Velocity::advectV(float dt, float *v, const float *prevV, const float *prevU) {
    float dt0 = dt * m_grid;
    for (int i = 1; i <= m_grid - 1; ++i) {
        for (int j = 1; j <= m_grid; ++j) {
            // reverse flow by vector field
            // use average staggered MAC grid velocity
            float x =
                    j - dt0 * 0.25f * (prevU[indexOfVelocityU(i, j - 1, m_grid)] + prevU[indexOfVelocityU(i, j, m_grid)]
                                       + prevU[indexOfVelocityU(i + 1, j - 1, m_grid)] +
                                       prevU[indexOfVelocityU(i + 1, j, m_grid)]);
            float y = i - dt0 * prevV[indexOfVelocityV(i, j, m_grid)];
            if (x < 0.5f) x = 0.5f; else if (x > m_grid + 0.5f) x = m_grid + 0.5f;
            if (y < 0.0f) y = 0.0f; else if (y > m_grid) y = m_grid;
            int xl = x, xr = xl + 1;
            int yl = y, yu = yl + 1;
            // Linear interpolate
            v[indexOfVelocityV(i, j, m_grid)] = linearInterpolate2D(
                    x - xl,
                    y - yl,
                    prevV[indexOfVelocityV(yl, xl, m_grid)],
                    prevV[indexOfVelocityV(yl, xr, m_grid)],
                    prevV[indexOfVelocityV(yu, xl, m_grid)],
                    prevV[indexOfVelocityV(yu, xr, m_grid)]
            );
        }
    }
    setVBoundary(v, m_grid);
}

//float Velocity::curl(int x, int y) {
//  return m_uQuantity[m_currentContext^1][indexOfVelocityU(y, x, m_grid)] - m_uQuantity[m_currentContext^1][indexOfVelocityU(y-1, x, m_grid)] + m_vQuantity[m_currentContext^1][indexOfVelocityV(y, x-1, m_grid)] - m_vQuantity[m_currentContext^1][indexOfVelocityV(y, x, m_grid)];
//}

float Velocity::dVOverDX(int i, int j) {
    return (m_vQuantity[m_currentContext ^ 1][indexOfVelocityV(i, j, m_grid)] -
            m_vQuantity[m_currentContext ^ 1][indexOfVelocityV(i, j - 1, m_grid)]);
}

float Velocity::dUOverDY(int i, int j) {
    return (m_uQuantity[m_currentContext ^ 1][indexOfVelocityU(i, j, m_grid)] -
            m_uQuantity[m_currentContext ^ 1][indexOfVelocityU(i - 1, j, m_grid)]);
}

float Velocity::curl(int x, int y) {
    return (dVOverDX(y, x) - dUOverDY(y, x)) / m_grid;
}

void Velocity::vorticityConfinement(float dt, float vorticity) {
    for (int i = 2; i < m_grid; ++i) {
        for (int j = 2; j < m_grid; ++j) {
            float w = curl(j, i);
            float u = curl(j, i - 1);
            float v = curl(j - 1, i);
            // FIXME nablaW check
            float nablaW[3] = {fabs(w - u) / m_grid, fabs(w - v) / m_grid, 0.0f};
            float normalizeFactor = sqrt(nablaW[0] * nablaW[0] + nablaW[1] * nablaW[1]);
            nablaW[0] /= (normalizeFactor + 1e-10);
            nablaW[1] /= (normalizeFactor + 1e-10);
            float force[3] = {vorticity * nablaW[1] * w, vorticity * -nablaW[0] * w, 0.0f};
            m_uQuantity[m_currentContext][indexOfVelocityU(i, j, m_grid)] =
                    m_uQuantity[m_currentContext ^ 1][indexOfVelocityU(i, j, m_grid)] + dt * force[0];
            m_vQuantity[m_currentContext][indexOfVelocityV(i, j, m_grid)] =
                    m_vQuantity[m_currentContext ^ 1][indexOfVelocityV(i, j, m_grid)] + dt * force[1];
        }
    }
    setUBoundary(m_uQuantity[m_currentContext], m_grid);
    setVBoundary(m_vQuantity[m_currentContext], m_grid);
}

//void Velocity::vorticityConfinement(float dt, float vorticity) {
//  for(int i = 2;i < m_grid;++i) {
//    for(int j = 2;j < m_grid;++j) {
//      float dx = fabsf(curl(j-1, i)) - fabsf(curl(j+1, i));
//      float dy = fabsf(curl(j, i+1)) - fabsf(curl(j, i-1));
//      double len = sqrt(dx*dx + dy*dy) + 1e-5;
//      dx *= vorticity / len;
//      dy *= vorticity / len;
//      m_uQuantity[m_currentContext][indexOfVelocityU(i, j, m_grid)] = m_uQuantity[m_currentContext^1][indexOfVelocityU(i, j, m_grid)] + dt * curl(j, i) * dx;
//      m_vQuantity[m_currentContext][indexOfVelocityV(i, j, m_grid)] = m_vQuantity[m_currentContext^1][indexOfVelocityV(i, j, m_grid)] + dt * curl(j, i) * dy;
//    }
//  }
//}

void Velocity::process(float dt, float diffusion, float *u, float *v) {
    // Add force
    addForce(dt);
    // Mass conservative
    massConserve(dt, 1.0f);

    m_currentContext ^= 1;
    vorticityConfinement(dt, 1.0f);
    massConserve(dt, 1.0f);

    m_currentContext ^= 1;
    advectU(dt, m_uQuantity[m_currentContext], m_uQuantity[m_currentContext ^ 1], m_vQuantity[m_currentContext ^ 1]);
    advectV(dt, m_vQuantity[m_currentContext], m_vQuantity[m_currentContext ^ 1], m_uQuantity[m_currentContext ^ 1]);

    // Mass conservative
    massConserve(dt, 1.0f);
}

void Velocity::massConserve(float dt, float materialDensity) {
    // dx * materialDensity / dt
    // float coefficient = materialDensity / dt * m_grid;

    // Use modified incomplete cholesky preconditioner conjugate gradient method
    // SparseMatrix<double> A;
    // A.resize(m_grid*m_grid, m_grid*m_grid);
    // VectorXd b(m_grid*m_grid), x(m_grid*m_grid);
    // vector<Triplet<double>> tripletOfA;
    //
    // int xdir[4] = {1, -1, 0, 0}, ydir[4] = {0, 0, 1, -1};
    // float possibleValue[4];
    //
    // for(int i = 0;i < m_grid;++i) {
    //   // Now it's solid boundary, if it's curved boundary, then I will implement it in future
    //   for(int j = 0;j < m_grid;++j) {
    //     int validGrid = 0;
    //     possibleValue[0] = m_uQuantity[m_currentContext^1][indexOfVelocityU(i, j+1, m_grid)];
    //     possibleValue[1] = -m_uQuantity[m_currentContext^1][indexOfVelocityU(i, j, m_grid)];
    //     possibleValue[2] = m_vQuantity[m_currentContext^1][indexOfVelocityV(i+1, j, m_grid)];
    //     possibleValue[3] = -m_vQuantity[m_currentContext^1][indexOfVelocityV(i, j, m_grid)];
    //     b(indexOfPressure(i, j, m_grid)) = 0.0f;
    //     for(int k = 0;k < 4;++k) {
    //       if(isInGrid(i+xdir[k], j+ydir[k], m_grid, m_grid)) {
    //         validGrid++;
    //         tripletOfA.push_back(Triplet<double>(indexOfPressure(i, j, m_grid), indexOfPressure(i+xdir[k], j+ydir[k], m_grid), -1));
    //         b(indexOfPressure(i, j, m_grid)) += coefficient * -possibleValue[k];
    //       }
    //     }
    //     tripletOfA.push_back(Triplet<double>(indexOfPressure(i, j, m_grid), indexOfPressure(i, j, m_grid), validGrid));
    //   }
    // }
    //
    // A.setFromTriplets(tripletOfA.begin(), tripletOfA.end());
    // ConjugateGradient<SparseMatrix<double>, Lower, IncompleteCholesky<double>> cg;
    // cg.compute(A);
    // x = cg.solve(b);
    // cout << "x:" << x << endl;
    // for(int i = 1;i <= m_grid;++i) {
    //   for(int j = 1;j <= m_grid-1;++j) {
    //     m_uQuantity[m_currentContext][indexOfVelocityU(i, j, m_grid)] -= (x(indexOfPressure(i, j+1, m_grid)) - x(indexOfPressure(i, j, m_grid))) / coefficient;
    //   }
    // }
    // for(int i = 1;i <= m_grid-1;++i) {
    //   for(int j = 1;j <= m_grid;++j) {
    //     m_vQuantity[m_currentContext][indexOfVelocityV(i, j, m_grid)] -= (x(indexOfPressure(i+1, j, m_grid)) - x(indexOfPressure(i, j, m_grid))) / coefficient;
    //   }
    // }
    // Use Gauss Seidel
    float *p = new float[(m_grid + 2) * (m_grid + 2)], *prevP = new float[(m_grid + 2) * (m_grid + 2)];
    for (int i = 1; i <= m_grid; ++i) {
        for (int j = 1; j <= m_grid; ++j) {
            prevP[indexOfPressure(i, j, m_grid)] = -(m_uQuantity[m_currentContext][indexOfVelocityU(i, j, m_grid)] -
                                                     m_uQuantity[m_currentContext][indexOfVelocityU(i, j - 1, m_grid)] +
                                                     m_vQuantity[m_currentContext][indexOfVelocityV(i, j, m_grid)] -
                                                     m_vQuantity[m_currentContext][indexOfVelocityV(i - 1, j,
                                                                                                    m_grid)]) / m_grid;
            p[indexOfPressure(i, j, m_grid)] = 0.0f;
        }
    }
    setBoundary(0, prevP, m_grid);
    setBoundary(0, p, m_grid);
    Solver *solver = new GaussSeidelSolver();
    solver->solve(p, prevP, 1.0f, 4.0f, 0, m_grid);
    for (int i = 1; i <= m_grid; ++i) {
        for (int j = 1; j <= m_grid - 1; ++j) {
            m_uQuantity[m_currentContext][indexOfVelocityU(i, j, m_grid)] -=
                    m_grid * (p[indexOfPressure(i, j + 1, m_grid)] - p[indexOfPressure(i, j, m_grid)]);
        }
    }
    for (int i = 1; i <= m_grid - 1; ++i) {
        for (int j = 1; j <= m_grid; ++j) {
            m_vQuantity[m_currentContext][indexOfVelocityV(i, j, m_grid)] -=
                    m_grid * (p[indexOfPressure(i + 1, j, m_grid)] - p[indexOfPressure(i, j, m_grid)]);
        }
    }
    delete prevP;
    delete p;
    setUBoundary(m_uQuantity[m_currentContext], m_grid);
    setVBoundary(m_vQuantity[m_currentContext], m_grid);

}

float *Velocity::getQuantity(int component) {
    if (component == uComponent) {
        return m_uQuantity[m_currentContext];
    } else if (component == vComponent) {
        return m_vQuantity[m_currentContext];
    } else {
        return nullptr;
    }
}

float *Velocity::getPrevQuantity(int component) {
    if (component == uComponent) {
        return m_uQuantity[m_currentContext ^ 1];
    } else if (component == vComponent) {
        return m_vQuantity[m_currentContext ^ 1];
    } else {
        return nullptr;
    }
}
