// -*- C++ -*-
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"

struct Rectangle {
  Point topLeft;
  Point bottomRight;
  Rectangle(Point topLeft, Point bottomRight)
    : topLeft(topLeft)
    , bottomRight(bottomRight)
  {
  }
};

#endif//RECTANGLE_H
