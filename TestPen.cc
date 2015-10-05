#include "Pen.h"
#include "LoggerNull.h"
#include <gtest/gtest.h>

TEST(ArcTest, TopRight) {
  std::shared_ptr<Logger> logger(std::make_shared<LoggerNull>());
  int32_t width = 800;
  int32_t height = 600;
  uint32_t *pixels = new uint32_t[width*height];
  std::shared_ptr<Canvas> canvas(std::make_shared<Canvas>(pixels, width, height));
  const Color white = 0xFFFFFFFF;
  const Color blue = 0xFF0000FF;
  Palette palette(white, blue);
  Pen pen(logger, canvas, 12, true, palette);
  pen.drawArc(300, 300, 100, 240, 330);
  pen.drawArc(100, 100, 40, 0, 359);

  /*
  EXPECT_EQ(1, Factorial(-5));
  EXPECT_EQ(1, Factorial(-1));
  EXPECT_GT(Factorial(-10), 0);
  */
}


TEST(LineTest, VerticalUp) {
  std::shared_ptr<Logger> logger(std::make_shared<LoggerNull>());
  int32_t width = 800;
  int32_t height = 600;
  uint32_t *pixels = new uint32_t[width*height];
  std::shared_ptr<Canvas> canvas(std::make_shared<Canvas>(pixels, width, height));
  const Color white = 0xFFFFFFFF;
  const Color blue = 0xFF0000FF;
  Palette palette(white, blue);
  Pen pen(logger, canvas, 4, false, palette);
  pen.drawLine(Point(300,300), Point(300, 200));
}

TEST(LineTest, VerticalDown) {
  std::shared_ptr<Logger> logger(std::make_shared<LoggerNull>());
  int32_t width = 800;
  int32_t height = 600;
  uint32_t *pixels = new uint32_t[width*height];
  std::shared_ptr<Canvas> canvas(std::make_shared<Canvas>(pixels, width, height));
  const Color white = 0xFFFFFFFF;
  const Color blue = 0xFF0000FF;
  Palette palette(white, blue);
  Pen pen(logger, canvas, 4, false, palette);
  pen.drawLine(Point(300,300), Point(300, 400));
}
