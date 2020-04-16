#pragma once
#include "Quantity.h"
class Velocity : public MultipleQuantity {
private:
  int m_grid;
  int m_currentContext;
  float *m_uQuantity[2];
  float *m_vQuantity[2];
  void addForce(float dt);
  void advectU(float dt, float *u, float *prevU, float *prevV);
  void advectV(float dt, float *v, float *prevV, float *prevU);
  float curl(int x, int y);
  void vorticityConfinement(float dt, float vorticity);
  void massConserve(float dt, float materialDensity);
public:
  Velocity(int N);
  ~Velocity();
  void process(float dt, float diffusion, float *u, float *v);
  float *getQuantity(int component) override;
  float *getPrevQuantity(int component) override;

  static const int uComponent = 1;
  static const int vComponent = 2;
};
