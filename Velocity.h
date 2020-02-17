#pragma once
#include "NavierStokes.h"
#include "Quantity.h"
class Velocity : public NavierStokes, public MultipleQuantity {
private:
  float *m_uQuantity[2];
  float *m_vQuantity[2];
  float *m_uQuantityAdjoint[2];
  float *m_vQuantityAdjoint[2];
  void project(float *p, float *div);
  void projectAdjoint(float *pAdjoint, float *divAdjoint);
public:
  Velocity(int N, Solver *solver);
  ~Velocity();
  void process(float dt, float diffusion, float *u, float *v) override;
  void processAdjoint(float dt, float diffusion, float *u, float *v, float *uAdjoint, float *vAdjoint) override;
  float *getQuantity(int component) override;
  float *getPrevQuantity(int component) override;

  static const int uComponent = 1;
  static const int vComponent = 2;
};
