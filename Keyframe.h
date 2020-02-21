#pragma once
#include "Density.h"
#include "Velocity.h"
#include <vector>
class Keyframe {
public:
  bool addDensityKeyframe(int t, Density *density);
  bool addVelocityKeyframe(int t, Velocity *velocity);

  Density *getDensityAtKeyframe(int t) const;
  Velocity *getVelocityAtKeyframe(int t) const;

  int getMaxKeyframeTime() const;

private:
  std::map<int, Density *> expectDensityMap;
  std::map<int, Velocity *> expectVelocityMap;
}
