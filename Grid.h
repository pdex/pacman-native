// -*- C++ -*-
#ifndef GRID_H
#define GRID_H

#include <iterator>
#include "CardinalMatrix.h"

class Grid {
  int width;
  int height;
  typedef std::vector<std::vector<bool>> BoolMatrix;
  BoolMatrix cells;
public:
  class Iterator : std::iterator<std::input_iterator_tag, CardinalMatrix> {
    int x;
    int y;
    Grid* grid;
    void increment() {
      x++;
      if (x >= grid->width) {
	x = 0;
	y += 1;
      }
      if (y >= grid->height) {
	x = -1;
	y = -1;
      }
    }
  public:
    Iterator() : x(-1), y(-1), grid(nullptr) {}
    Iterator(int x, int y, Grid* grid) : x(x), y(y), grid(grid) {}
    int getX() {
      return x;
    }
    int getY() {
      return y;
    }
    CardinalMatrix deref() const {
      return grid->matrixAt(x, y);
    }
    CardinalMatrix operator*() const {
      return deref();
    }
    std::shared_ptr<CardinalMatrix> operator->() const {
      return std::make_shared<CardinalMatrix>(deref());
    }
    Iterator& operator++() {
      increment();
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      increment();
      return tmp;
    }
    bool operator==(Iterator const & other) const {
      return x == other.x && y == other.y;
    }
    bool operator!=(Iterator const & other) const {
      return !(*this == other);
    }
  };
  Grid() {}
  Grid(int width, int height, bool initialValue)
    : width(width)
    , height(height)
  {
    std::vector<bool> initial(height, initialValue);
    cells = BoolMatrix(width, initial);
  }
  std::vector<bool>& operator[](int x) {
    return cells[x];
  }
  CardinalMatrix matrixAt(int x, int y) {
    CardinalMatrix matrix(x, y);
    matrix.set(CardinalMatrix::HERE, (*this)[x][y]);
    if ((x-1) >= 0) {
      if ((y-1) >= 0) {
	matrix.set(CardinalMatrix::NW, (*this)[x-1][y-1]);
      }
      matrix.set(CardinalMatrix::W, (*this)[x-1][y]);
      if ((y+1) < height) {
	matrix.set(CardinalMatrix::SW, (*this)[x-1][y+1]);
      }
    }
    if ((x+1) < width) {
      if ((y-1) >= 0) {
	matrix.set(CardinalMatrix::NE, (*this)[x+1][y-1]);
      }
      matrix.set(CardinalMatrix::E, (*this)[x+1][y]);
      if ((y+1) < height) {
	matrix.set(CardinalMatrix::SE, (*this)[x+1][y+1]);
      }
    }
    if ((y-1) >= 0) {
      matrix.set(CardinalMatrix::N, (*this)[x][y-1]);
    }
    if ((y+1) < height) {
      matrix.set(CardinalMatrix::S, (*this)[x][y+1]);
    }
    return matrix;
  }
  Iterator begin() {
    return Iterator(0, 0, this);
  }
  Iterator end() {
    return Iterator();
  }
};

#endif//GRID_H
