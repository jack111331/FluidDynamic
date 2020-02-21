#include "Derivative.h"

QuantityDerivative::QuantityDerivative(int N) {
  m_densityDerivative = new float[(N+2)*(N+2)];
  m_uDerivative = new float[(N+2)*(N+2)];
  m_vDerivative = new float[(N+2)*(N+2)];
}
