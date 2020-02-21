#pragma once
#include "NavierStokes.h"
#include "Quantity.h"
class Density final : public NavierStokesHelper<Density>, public SingleQuantity {
private:
  float *m_quantity[2];

public:
  Density(int N, Solver *solver);
  Velocity(const Velocity &v); // copy ctor.
  ~Density();
  void process(float dt, float diffusion, float *u, float *v);
  void processDerivative(float dt, float diffusion, float *u, float *v);
  float *getQuantity() override;
  float *getPrevQuantity() override;
};
