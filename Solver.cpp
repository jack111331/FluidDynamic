#include <ShaderUtility.h>
#include "Solver.h"
#include "Utility.h"

//void GaussSeidelSolver::solve(uint32_t x, uint32_t x0, float a, float denom) {
//    for (int k = 0; k < m_iterativeTime; ++k) {
//        // location = 0: quantity
//        // location = 1: previous quantity
//        GAUSS_SEIDEL_SOLVER_PROGRAM.bind();
//        GAUSS_SEIDEL_SOLVER_PROGRAM.bindBuffer(x, 0);
//        GAUSS_SEIDEL_SOLVER_PROGRAM.bindBuffer(x0, 1);
//        GAUSS_SEIDEL_SOLVER_PROGRAM.uniform1f("a", a);
//        GAUSS_SEIDEL_SOLVER_PROGRAM.uniform1f("denom", denom);
//        GAUSS_SEIDEL_SOLVER_PROGRAM.dispatch(1, 1, 1);
//
//        ShaderUtility::SET_DENSITY_BOUND_PROGRAM.bind();
//        ShaderUtility::SET_DENSITY_BOUND_PROGRAM.bindBuffer(x, 0);
//        ShaderUtility::SET_DENSITY_BOUND_PROGRAM.dispatch(1, 1, 1);
//    }
//}

void JacobiSolver::solve(uint32_t xOut, uint32_t x, uint32_t x0, float a, float denom, int N) {
    for (int k = 0; k < m_iterativeTime; ++k) {
        // location = 0: quantity
        // location = 1: previous quantity
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.bind();
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.bindBuffer(x, 0);
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.bindBuffer(x0, 1);
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.uniform1f("a", a);
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.uniform1f("denom", denom);
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.dispatch(N + 2, N + 2, 1);

        m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bind();
        m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bindBuffer(x, 0);
        m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.dispatch(1, 1, 1);
    }
}
