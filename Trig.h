// -*- C++ -*-
#ifndef TRIG_H
#define TRIG_H

#include <cmath>
#include "Degrees.h"
#include "Point.h"

class Trig {
public:
  Trig() {
  }
  static Point hypotenuse(Point origin, int32_t radius, Degrees angle) {
    return Point(
      origin.x + radius * std::cos(angle.radians()),
      origin.y - radius * std::sin(angle.radians())
    );
  }
};

#endif//TRIG_H
