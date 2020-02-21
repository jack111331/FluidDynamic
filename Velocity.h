#pragma once
#include "NavierStokes.h"
#include "Quantity.h"
class Velocity final : public NavierStokesHelper<Velocity>, public MultipleQuantity {
private:
  float *m_uQuantity[2];
  float *m_vQuantity[2];
  void project(float *u, float *v, float *p, float *div);
public:
  Velocity(int N, Solver *solver);
  Velocity(const Velocity &v); // copy ctor.
  ~Velocity();
  void process(float dt, float diffusion, float *u, float *v, const std::vector<ControlForce *> &controlForceList);
  void processDerivative(float dt, float diffusion, float *u, float *v, const std::vector<ControlForce *> &controlForceList);
  float *getQuantity(int component) override;
  float *getPrevQuantity(int component) override;


  static const int uComponent = 1;
  static const int vComponent = 2;
};
