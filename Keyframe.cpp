#include "Keyframe.h"

bool Keyframe::addDensityKeyframe(int t, Density *density) {
  if(expectDensityMap.find(t) == expectDensityMap.end()) {
    expectDensityMap.insert(std::pair<int, Density *>(t, density));
    return true;
  }
  return false;
}
bool Keyframe::addVelocityKeyframe(int t, Velocity *velocity) {
  if(expectVelocityMap.find(t) == expectVelocityMap.end()) {
    expectVelocityMap.insert(std::pair<int, Velocity *>(t, velocity));
    return true;
  }
  return false;
}

int Keyframe::getMaxKeyframeTime() const {
  return std::max((--expectDensityMap.end()).first, (--expectVelocityMap.end()).first);
}
