#pragma once

class GaussSeidelSolver : public Solver {
public:
    GaussSeidelSolver() : m_iterativeTime(20) {};

    GaussSeidelSolver(int iterativeTime) : m_iterativeTime(iterativeTime) {};

    void solve(float *x, float *x0, float a, float denom, int boundary, int N);

private:
    int m_iterativeTime;
};

