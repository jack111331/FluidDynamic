#include "Optimization.h"

Optimization::Optimization() : m_objective(0.0f), m_objectiveDerivate(0.0f) {}

void Optimization::evaluate(int N, std::vector<ControlForce *> controlForceList, Keyframe *targetKeyframe, const Density *initDensity, const Velocity *initVelocity) {
  // Initial Setup
  Solver *solver = new GaussSeidelSolver(timestep);
  Density *densityField;
  Density *densityDerivativeField = new Density(N, solver);
  Velocity *velocityField;
  Velocity *velocityDerivativeField = new Velocity(N, solver);
  if(initDensity == nullptr) {
    densityField = new Density(N, solver);
  } else {
    densityField = initDensity.clone();
  }

  if(initVelocity == nullptr) {
    velocityField = new Velocity(N, solver);
  } else {
    velocityField = initVelocity.clone();
  }

  for(int t = 1;t <= targetKeyframe->getMaxKeyframeTime();++t) {
    // Reorder its algorithm to have more space to utilize
    // Store force, velocity field, and density field
    // TODO Store force
    Density *prevDensity = densityField.clone();
    Velocity *prevVelocity = velocityField.clone();

    for(auto controlForce : controlForceList) {
      float *forceDerivate = new float[(N+2)*(N+2)];
    }
    // Compute force derivative
    // Add force derivative to velocity derivative

  }

  // Clear Out
  delete densityDerivativeField;
  delete velocityDerivativeField;
  if(initDensity == nullptr) {
    delete densityField;
  }
  if(initVelocity == nullptr) {
    delete velocityField;
  }

  // return cost function and its derivative over all control vector u
}
