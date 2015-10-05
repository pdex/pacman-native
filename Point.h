// -*- C++ -*-
#ifndef POINT_H
#define POINT_H

#include <ostream>

struct Point {
  const int32_t x;
  const int32_t y;
  Point(int32_t x, int32_t y) : x(x), y(y) {
  }
  Point translateX(int32_t delta) {
    return Point(x + delta, y);
  }
  Point translateY(int32_t delta) {
    return Point(x, y + delta);
  }
  Point transalteXY(int32_t deltaX, int32_t deltaY) {
    return Point(x + deltaX, y + deltaY);
  }
  friend std::ostream & operator<<(std::ostream &out, Point p) {
    out << p.x << "," << p.y;
    return out;
  }
};

#endif//POINT_H
