#pragma once
#include "Solver.h"
#include <vector>

class NavierStokes {
protected:
  static std::vector<float *> heap;
  int m_grid;
  Solver *m_solver;
  int m_currentContext;
  int m_currentContextAdjoint;

  void addQuantity(float dt, float *quantity, float *adder);
  void diffuse(float dt, float diffusion, int boundary, float *quantity, float *prevQuantity);
  void advect(float dt, int boundary, float *u, float *v, float *quantity, float *prevQuantity);

  void pushHeap(const float *content);
  void popHeap(float *content);

  void addQuantityAdjoint(float dt, float *quantityAdjoint, float *adderAdjoint);
  void diffuseAdjoint(float dt, float diffusion, int boundary, float *quantityAdjoint, float *prevQuantityAdjoint);
  void advectAdjoint(float dt, int boundary, float *u, float *v, float *uAdjoint, float *vAdjoint, float *prevQuantity, float *quantityAdjoint, float *prevQuantityAdjoint);

public:
  NavierStokes(int N, Solver *solver);
  virtual void process(float dt, float diffusion, float *u, float *v) = 0;
  virtual void processAdjoint(float dt, float diffusion, float *u, float *v, float *uAdjoint, float *vAdjoint) = 0;
};
