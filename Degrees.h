// -*- C++ -*-
#ifndef DEGREES_H
#define DEGREES_H

#include <cmath>

class Degrees {
  const double pi = std::acos(-1);
  const uint32_t degrees;
public:
  Degrees(uint32_t degrees) : degrees(degrees) {
  }
  Radians radians() {
    return Radians(degrees * (pi / 180.0));
  }

  operator uint32_t() { return degrees; }
};

inline Degrees operator "" _Degrees(unsigned long long int degrees) {
  return Degrees(degrees);
}

#endif//DEGREES_H
