// -*- C++ -*-
#ifndef CARDINAL_MATRIX_H
#define CARDINAL_MATRIX_H

#include <vector>
#include "Point.h"

class CardinalMatrix {
  int x;
  int y;
  std::vector<bool> cells;
public:
  enum Location {
    NW,
    N,
    NE,
    W,
    HERE,
    E,
    SW,
    S,
    SE
  };
  CardinalMatrix(int x, int y, bool initialValue=false)
    : x(x)
    , y(y)
    , cells(9, initialValue)
  {
  }

  Point point() {
    return Point(x, y);
  }

  void set(Location location, bool value) {
    cells[location] = value;
  }

  bool operator[](Location location) {
    return cells[location];
  }
  friend std::ostream & operator<<(std::ostream &out, CardinalMatrix matrix) {
    out << " NW: " << matrix.cells[NW]
	<< " N: " << matrix.cells[N]
	<< " NE: " << matrix.cells[NE]
	<< " W: " << matrix.cells[W]
	<< " HERE: " << matrix.cells[HERE]
	<< " E: " << matrix.cells[E]
	<< " SW: " << matrix.cells[SW]
	<< " S: " << matrix.cells[S]
	<< " SE: " << matrix.cells[SE]
	<< ", (" << matrix.x << "," << matrix.y << ")";
    return out;
  }
};

#endif//CARDINAL_MATRIX_H
