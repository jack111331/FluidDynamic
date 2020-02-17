#pragma once

class Solver {
  public:
    virtual void solve(float *x, float *x0, float a, float denom, int boundary, int N) = 0;
    virtual void solveAdjoint(float *xAdjoint, float *x0Adjoint, float a, float denom, int boundary, int N) override;
};

class GaussSeidelSolver : public Solver {
  private:
  int m_iterativeTime;
  public:
    GaussSeidelSolver();
    GaussSeidelSolver(int iterativeTime);
    void solve(float *x, float *x0, float a, float denom, int boundary, int N) override;
    void solveAdjoint(float *xAdjoint, float *x0Adjoint, float a, float denom, int boundary, int N) override;
};

class ConjugatedGradientSolver : public Solver {
  public:
    void solve(float *x, float *x0, float a, float denom, int boundary, int N) override;
    void solveAdjoint(float *xAdjoint, float *x0Adjoint, float a, float denom, int boundary, int N) override;
};
