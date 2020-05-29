#include <ShaderUtility.h>
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
        GAUSS_SEIDEL_SOLVER_PROGRAM.dispatch(1, 1, 1);

        ShaderUtility::SET_DENSITY_BOUND_PROGRAM.bind();
        ShaderUtility::SET_DENSITY_BOUND_PROGRAM.bindBuffer(x, 0);
        ShaderUtility::SET_DENSITY_BOUND_PROGRAM.dispatch(1, 1, 1);
    }
}
