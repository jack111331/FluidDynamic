#pragma once
#include "NavierStokes.h"
#include "Quantity.h"
class Velocity : public NavierStokes, public MultipleQuantity {
private:
  float *m_uQuantity[2];
  float *m_vQuantity[2];
  void project(float *u, float *v, float *p, float *div);
public:
  Velocity(int N, Solver *solver);
  ~Velocity();
  void process(float dt, float diffusion, float *u, float *v) override;
  float *getQuantity(int component) override;
  float *getPrevQuantity(int component) override;

  static const int uComponent = 1;
  static const int vComponent = 2;
};
