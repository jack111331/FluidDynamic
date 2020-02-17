#include "Solver.h"
#include "Utility.h"

GaussSeidelSolver::GaussSeidelSolver() : m_iterativeTime(20){

}

GaussSeidelSolver::GaussSeidelSolver(int iterativeTime) : m_iterativeTime(iterativeTime){

}

void GaussSeidelSolver::solve(float *x, float *x0, float a, float denom, int boundary, int N) {
  for(int k = 0;k < m_iterativeTime;++k) {
    // Ax = x0
    for(int i = 1;i <= N;++i) {
      for(int j = 1;j <= N;++j) {
        x[indexOf(i, j, N)] = (x0[indexOf(i, j, N)] + a * (x[indexOf(i-1, j, N)] + x[indexOf(i+1, j, N)] + x[indexOf(i, j-1, N)] + x[indexOf(i, j+1, N)])) / denom;
      }
    }
    setBoundary(boundary, x, N);
  }
}
void GaussSeidelSolver::solveAdjoint(float *xAdjoint, float *x0Adjoint, float a, float denom, int boundary, int N) {
  for(int k = m_iterativeTime;k >= 0;--k) {
    setBoundaryAdjoint(boundary, xAdjoint, N);
    // Ax = x0
    for(int j = N;j >= 1;--j) {
      for(int i = N;i >= 1;i++) {
        xAdjoint[indexOf(i, j+1, N)] += a * x0Adjoint[indexOf(i, j, N)]/denom;
        xAdjoint[indexOf(i, j-1, N)] += a * x0Adjoint[indexOf(i, j, N)]/denom;
        xAdjoint[indexOf(i+1, j, N)] += a * x0Adjoint[indexOf(i, j, N)]/denom;
        xAdjoint[indexOf(i-1, j, N)] += a * x0Adjoint[indexOf(i, j, N)]/denom;
        x0Adjoint[indexOf(i, j, N)] += x0Adjoint[indexOf(i, j, N)]/denom;
        xAdjoint[indexOf(i-1, j, N)] = 0.0f;
      }
    }
  }
}
