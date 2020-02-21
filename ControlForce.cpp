#include "ControlForce.h"
#include "Velocity.h"

GaussianWindForce::GaussianWindForce(float direction, int centerX, int centerY) : m_direction(direction), m_center({centerX, centerY}) {

}

void GaussianWindForce::applyForce(Velocity *velocityField, int N) {
  float *u = velocityField->getQuantity(Velocity::uComponent);
  float *v = velocityField->getQuantity(Velocity::vComponent);

  float uDirection = sin(m_direction), vDirection = cos(m_direction);
  for(int i = max(m_center[0] - GRIDWIDTH, 1);i <= min(m_center[0] + GRIDWIDTH, N);++i) {
    for(int j = max(m_center[1] - GRIDWIDTH, 1);j <= min(m_center[1] + GRIDWIDTH, N);++j) {
      int deltaC[2] = {m_center[0] - i, m_center[1] - j};
      float gaussFalloff = exp(-GAUSSIANWIDTH * (deltaC[0] * deltaC[0] + deltaC[1] * deltaC[1]));
      u[indexOf(i, j, N)] += gaussFalloff * uDirection;
      v[indexOf(i, j, N)] += gaussFalloff * vDirection;
    }
  }
}

void GaussianWindForce::applyForceDerivative(Velocity *velocityField, int N) {
}

VortexForce::VortexForce(float r, int centerX, int centerY) : m_r(r), m_center({centerX, centerY}) {

}

void VortexForce::applyForce(Velocity *velocityField, int N) {
  float *u = velocityField->getQuantity(Velocity::uComponent);
  float *v = velocityField->getQuantity(Velocity::vComponent);

  for(int i = max(m_center[0] - GRIDWIDTH, 1);i <= min(m_center[0] + GRIDWIDTH, N);++i) {
    for(int j = max(m_center[1] - GRIDWIDTH, 1);j <= min(m_center[1] + GRIDWIDTH, N);++j) {
      int deltaC[2] = {m_center[0] - i, m_center[1] - j};
      float uDirection = -deltaC[1], vDirection = deltaC[0];
      float gaussFalloff = exp(-GAUSSIANWIDTH * (deltaC[0] * deltaC[0] + deltaC[1] * deltaC[1]));
      u[indexOf(i, j, N)] += m_r * gaussFalloff * uDirection;
      v[indexOf(i, j, N)] += m_r * gaussFalloff * vDirection;
    }
  }
}

void VortexForce::applyForceDerivative(Velocity *velocityField, int N) {
}
