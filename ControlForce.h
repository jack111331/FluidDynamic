#pragma once

class Velocity;
class ControlForce {
public:
  virtual void applyForce(Velocity *velocityField, int N) = 0;
  virtual void applyForceDerivative(Velocity *velocityField, int N) = 0;
};
class GaussianWindForce final : public ControlForce {
public:
  GaussianWindForce(float direction, int centerX, int centerY);
  void applyForce(Velocity *velocityField, int N) override;
  void applyForceDerivative(Velocity *velocityField, int N) override;
private:
  // TODO assign contant value
  const int GRIDWIDTH;
  const float GAUSSIANWIDTH;
  float m_direction; // Use rad representation.
  int m_center[2];
};
class VortexForce final : public ControlForce {
public:
  VortexForce(float r, int centerX, int centerY);
  void applyForce(Velocity *velocityField, int N) override;
  void applyForceDerivative(Velocity *velocityField, int N) override;
private:
  // TODO assign contant value
  const int GRIDWIDTH;
  const float GAUSSIANWIDTH;
  float m_r; // Use rad representation.
  int m_center[2];
};
