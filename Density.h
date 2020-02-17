#pragma once
#include "NavierStokes.h"
#include "Quantity.h"
class Density : public NavierStokes, public SingleQuantity {
private:
  float *m_quantity[2];
  float *m_quantityAdjoint[2];

public:
  Density(int N, Solver *solver);
  ~Density();
  void process(float dt, float diffusion, float *u, float *v) override;
  void processAdjoint(float dt, float diffusion, float *u, float *v, float *uAdjoint, float *vAdjoint) override;
  float *getQuantity() override;
  float *getPrevQuantity() override;
};
