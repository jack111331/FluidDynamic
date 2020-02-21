#pragma once
#include <vector>
class Optimization {
public:
  Optimization();
  // take in control vector u : {u_k}
  void evaluate(int N, std::vector<ControlForce *> controlForceList, Keyframe *targetKeyframe, Density *initDensity = nullptr, Velocity *initVelocity = nullptr);

  float m_objective, m_objectiveDerivate;
};
