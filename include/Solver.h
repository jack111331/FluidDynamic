#pragma once

class Solver {
public:
    virtual void solve(float *x, float *x0, float a, float denom, int boundary, int N) = 0;
    virtual ~Solver() = 0;
};

class GaussSeidelSolver : public Solver {
private:
    int m_iterativeTime;
public:
    GaussSeidelSolver();

    GaussSeidelSolver(int iterativeTime);

    void solve(float *x, float *x0, float a, float denom, int boundary, int N) override;
};

class ConjugatedGradientSolver : public Solver {
public:
    ConjugatedGradientSolver();

    void solve(float *x, float *x0, float a, float denom, int boundary, int N) override;
};
