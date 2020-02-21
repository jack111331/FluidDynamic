#pragma once

class QuantityDerivative {
public:
  QuantityDerivative(int N);
private:
  float *m_densityDerivative;
  float *m_uDerivative;
  float *m_vDerivative;
};
