#pragma once
#include "NavierStokes.h"
#include "Quantity.h"
class Density : public NavierStokes, public SingleQuantity {
private:
  float *m_quantity[2];

public:
  Density(int N, Solver *solver);
  ~Density();
  void clear();
  void clearPrev();
  void process(float dt, float diffusion, float *u, float *v) override;
  float *getQuantity() override;
  float *getPrevQuantity() override;
};
