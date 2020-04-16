#pragma once

class SingleQuantity {
public:
  virtual float *getQuantity() = 0;
  virtual float *getPrevQuantity() = 0;
};

class MultipleQuantity {
public:
  virtual float *getQuantity(int component) = 0;
  virtual float *getPrevQuantity(int component) = 0;
};
