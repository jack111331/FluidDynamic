#pragma once


#include "Shader.h"

class GaussSeidelSolver {
public:
    GaussSeidelSolver() : m_iterativeTime(20) {};

    GaussSeidelSolver(int iterativeTime) : m_iterativeTime(iterativeTime) {};

    void solve(uint32_t x, uint32_t x0, float a, float denom);

private:
    int m_iterativeTime;

    static constexpr char GAUSS_SEIDEL_SOLVER_PROGRAM_PATH[] = "resources/shader/compute/GaussSeidel.cs";
    const Shader GAUSS_SEIDEL_SOLVER_PROGRAM = Shader(GaussSeidelSolver::GAUSS_SEIDEL_SOLVER_PROGRAM_PATH);
};

