#include "Solver.h"
#include "Utility.h"

void GaussSeidelSolver::solve(uint32_t x, uint32_t x0, float a, float denom) {
    for (int k = 0; k < m_iterativeTime; ++k) {
        // location = 0: quantity
        // location = 1: previous quantity
        GAUSS_SEIDEL_SOLVER_PROGRAM.bind();
        GAUSS_SEIDEL_SOLVER_PROGRAM.bindBuffer(x, 0);
        GAUSS_SEIDEL_SOLVER_PROGRAM.bindBuffer(x0, 1);
        GAUSS_SEIDEL_SOLVER_PROGRAM.uniform1f("a", a);
        GAUSS_SEIDEL_SOLVER_PROGRAM.uniform1f("denom", denom);
        GAUSS_SEIDEL_SOLVER_PROGRAM.dispatch();

        // Ax = x0
//        for (int i = 1; i <= N; i++) {
//            for (int j = 1; j <= N; j++) {
//                x[indexOf(i, j, N)] = (x0[indexOf(i, j, N)] + a * (x[indexOf(i - 1, j, N)] + x[indexOf(i + 1, j, N)] +
//                                                                   x[indexOf(i, j - 1, N)] + x[indexOf(i, j + 1, N)])) /
//                                      denom;
//            }
//        }
        // TODO set boundary manually after each solve invoke
//        setBoundary(boundary, x, N);
    }
}
