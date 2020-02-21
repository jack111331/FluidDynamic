#pragma once
#include "Solver.h"
#include <vector>
#include "ControlForce.h"

class NavierStokes {
protected:
  int m_grid;
  Solver *m_solver;
  int m_currentContext;

  void addQuantity(float dt, float *quantity, float *adder);
  void diffuse(float dt, float diffusion, int boundary, float *quantity, float *prevQuantity);
  void advect(float dt, int boundary, float *u, float *v, float *quantity, float *prevQuantity);

  void advectDerivative(float dt, int boundary, float *u, float *v, float *quantityDerivative, float *prevQuantityDerivative);

public:
  NavierStokes(int N, Solver *solver);
};

template <class DerivedClass>
class NavierStokesHelper : public NavierStokes {
public:
  virtual DerivedClass* clone() const {
    return new DerivedClass(static_cast<const DerivedClass&>(*this)); // call the copy ctor.
  }
};
