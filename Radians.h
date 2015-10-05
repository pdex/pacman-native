// -*- C++ -*-
#ifndef RADIANS_H
#define RADIANS_H

class Radians {
  const double radians;
public:
  Radians(double radians) : radians(radians) {
  }

  operator double() {
    return radians;
  }
};

#endif//RADIANS_H
