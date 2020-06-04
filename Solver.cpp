#include <ShaderUtility.h>
#include <GL/glew.h>
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

void JacobiSolver::solve(uint32_t x, uint32_t x0, float a, float denom, int N) {
    uint32_t temp;
    glGenBuffers(1, &temp);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, temp);
    glBufferData(GL_SHADER_STORAGE_BUFFER, (N + 2) * (N + 2) * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    for (int k = 0; k < m_iterativeTime; ++k) {
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.bind();
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.bindBuffer(x, 0);
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.bindBuffer(x0, 1);
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.bindBuffer(temp, 2);
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.uniform1f("a", a);
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.uniform1f("denom", denom);
        m_shaderUtility->JACOBI_SOLVER_PROGRAM.dispatch(N, N, 1);

        m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bind();
        m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.bindBuffer(temp, 0);
        m_shaderUtility->SET_DENSITY_BOUND_PROGRAM.dispatch(1, 1, 1);

        glBindBuffer(GL_COPY_READ_BUFFER, temp);
        glBindBuffer(GL_COPY_WRITE_BUFFER, x);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, (N + 2) * (N + 2) * sizeof(float));
        glMemoryBarrier(GL_SHADER_STORAGE_BUFFER);
    }
    glDeleteBuffers(1, &temp);
}
