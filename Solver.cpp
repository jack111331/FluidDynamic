#include "Solver.h"
#include "Utility.h"

Solver::~Solver() {

}

GaussSeidelSolver::GaussSeidelSolver() : m_iterativeTime(20) {

}

GaussSeidelSolver::GaussSeidelSolver(int iterativeTime) : m_iterativeTime(iterativeTime) {

}

void GaussSeidelSolver::solve(float *x, float *x0, float a, float denom, int boundary, int N) {
    for (int k = 0; k < m_iterativeTime; ++k) {
        // Ax = x0
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                x[indexOf(i, j, N)] = (x0[indexOf(i, j, N)] + a * (x[indexOf(i - 1, j, N)] + x[indexOf(i + 1, j, N)] +
                                                                   x[indexOf(i, j - 1, N)] + x[indexOf(i, j + 1, N)])) /
                                      denom;
            }
        }
        setBoundary(boundary, x, N);
    }
}
