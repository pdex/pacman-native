#include "Grid.h"
#include <gtest/gtest.h>

TEST(GridTest, Iterate) {
  Grid grid(20, 7, false);
  /*
%%%%%%%%%%%%%%%%%%%%
%......%G  G%......%
%.%%...%%  %%...%%.%
%.%o.%........%.o%.%
%.%%.%.%%%%%%.%.%%.%
%........P.........%
%%%%%%%%%%%%%%%%%%%%
   */
  for (auto it : grid[0]) {
    it = true;
  }
  grid[1][0] = true;
  grid[1][7] = true;
  grid[1][12] = true;
  grid[1][19] = true;

  grid[2][0] = true;
  grid[2][2] = true;
  grid[2][3] = true;
  grid[2][7] = true;
  grid[2][8] = true;
  grid[2][11] = true;
  grid[2][12] = true;
  grid[2][16] = true;
  grid[2][17] = true;
  grid[2][19] = true;

  EXPECT_EQ(true, grid[0][0]);

  Grid::Iterator end;
  EXPECT_EQ(-1, end.getX());
  EXPECT_EQ(-1, end.getY());
  Grid::Iterator it = grid.begin();
  int x = 0;
  int y = 0;

  it++;
  EXPECT_EQ(1, it.getX());
  EXPECT_EQ(0, it.getY());

  it = grid.begin();
  while(it != grid.end()) {
    EXPECT_EQ(x, it.getX());
    EXPECT_EQ(y, it.getY());
    x++;
    if (x >= 20) {
      x = 0;
      y++;
    }
    if (y >= 7) {
      x = -1;
      y = -1;
    }
    it++;
    break;
  }

  for (CardinalMatrix matrix : grid) {
    Point p = matrix.point();
    if (p.x == 0 && p.y == 0) {
      EXPECT_EQ(false, matrix[CardinalMatrix::NW]);
      EXPECT_EQ(false, matrix[CardinalMatrix::N]);
      EXPECT_EQ(false, matrix[CardinalMatrix::NE]);
      EXPECT_EQ(false, matrix[CardinalMatrix::W]);
      EXPECT_EQ(true, matrix[CardinalMatrix::HERE]);
      EXPECT_EQ(true, matrix[CardinalMatrix::E]);
      EXPECT_EQ(false, matrix[CardinalMatrix::SW]);
      EXPECT_EQ(true, matrix[CardinalMatrix::S]);
      EXPECT_EQ(false, matrix[CardinalMatrix::SE]);
    }
  }

  /*
  EXPECT_EQ(1, Factorial(-5));
  EXPECT_EQ(1, Factorial(-1));
  EXPECT_GT(Factorial(-10), 0);
  */
}
