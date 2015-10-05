// -*- C++ -*-
#ifndef VIEW_H
#define VIEW_H

#include "Canvas.h"
#include "CardinalMatrix.h"
#include "GameState.h"
#include "Grid.h"
#include "Logger.h"
#include "Palette.h"
#include "Pen.h"
#include "Point.h"

namespace {
  const uint32_t kOpaqueColorMask = 0xff000000;  // Opaque pixels.
  const uint32_t kWhiteMask = 0xffffff;
  const uint32_t kBlueMask = 0xFF0000FF;
  const double kWallRadius = 0.15;
}

class View {
  std::shared_ptr<Canvas> canvas;
  std::shared_ptr<Logger> logger;
  const int32_t gridSize;
public:
  View(std::shared_ptr<Canvas> canvas, std::shared_ptr<Logger> logger)
    : canvas(canvas)
    , logger(logger)
    , gridSize(30)
  {
  }

  Point project(Point point) {
    return Point((point.x + 1) * gridSize, (point.y + 1) * gridSize);
  }
  
  void drawWallNE(Point point, CardinalMatrix matrix) {
    //    Palette palette(kBlueMask, kWhiteMask);
    Palette palette(0xFFFFFFFF, kWhiteMask);
    Pen pen(logger, canvas, 2, false, palette);
    //    pen.debug(true);
    if (not matrix[CardinalMatrix::N] && not matrix[CardinalMatrix::E]) {
      pen.drawArc(point, kWallRadius * gridSize, 0_Degrees, 91_Degrees);
    }
    if (matrix[CardinalMatrix::N] && not matrix[CardinalMatrix::E]) {
      Point from(point.translateX(gridSize * kWallRadius));
      Point to(from.translateY(gridSize * -0.5 - 1));
      pen.drawLine(from, to);
    }
    if (not matrix[CardinalMatrix::N] && matrix[CardinalMatrix::E]) {
      Point from(point.translateY(gridSize * -1 * kWallRadius));
      Point to(from.translateX(gridSize * 0.5 -1));
      pen.drawLine(from, to);
    }
    if (matrix[CardinalMatrix::N] && matrix[CardinalMatrix::E] && not matrix[CardinalMatrix::NE] ) {
      Point outerPoint(point.x + gridSize * 2 * kWallRadius, point.y + gridSize * -2 * kWallRadius);
      pen.drawArc(outerPoint, kWallRadius * gridSize-1, 180_Degrees, 271_Degrees);

      Point from1(point.x + gridSize * 2 * kWallRadius - 1, point.y + gridSize * -1 * kWallRadius);
      Point to1(point.x + gridSize * 0.5 + 1, point.y + gridSize * -1 * kWallRadius);
      pen.drawLine(from1, to1);

      Point from2(point.x + gridSize * kWallRadius, point.y + gridSize * -2 * kWallRadius + 1);
      Point to2(point.x + gridSize * kWallRadius, point.y + gridSize * -0.5);
      pen.drawLine(from2, to2);
    }
  }

  void drawWallSE(Point point, CardinalMatrix matrix) {
    //    Palette palette(kBlueMask, kWhiteMask);
    Palette palette(0xFF00FF00, kWhiteMask);
    Pen pen(logger, canvas, 2, false, palette);
    if (not matrix[CardinalMatrix::S] and not matrix[CardinalMatrix::E]) {
      pen.drawArc(point, kWallRadius * gridSize, 270_Degrees, 361_Degrees);
    }
    if (matrix[CardinalMatrix::S] and not matrix[CardinalMatrix::E]) {
      Point from(point.x + gridSize * kWallRadius, point.y);
      Point to(point.x + gridSize * kWallRadius, point.y + gridSize * 0.5 + 1);
      pen.drawLine(from, to);
    }
    if (not matrix[CardinalMatrix::S] and matrix[CardinalMatrix::E]) {
      Point from(point.x, point.y + gridSize * kWallRadius);
      Point to(point.x + gridSize * 0.5 + 1, point.y + gridSize * kWallRadius);
      pen.drawLine(from, to);
    }
    if (matrix[CardinalMatrix::S] and matrix[CardinalMatrix::E] and not matrix[CardinalMatrix::SE]) {
      Point outerPoint(point.x + gridSize * 2 * kWallRadius, point.y + gridSize * 2 * kWallRadius);
      pen.drawArc(outerPoint, kWallRadius * gridSize - 1, 90_Degrees, 179_Degrees);
      Point from1(point.x + gridSize * 2 * kWallRadius -1, point.y + gridSize * kWallRadius);
      Point to1(point.x + gridSize * 0.5, point.y + gridSize * kWallRadius);
      pen.drawLine(from1, to1);
      Point from2(point.x + gridSize * kWallRadius, point.y + gridSize * 2 * kWallRadius - 1);
      Point to2(point.x + gridSize * kWallRadius, point.y + gridSize * 0.5);
      pen.drawLine(from2, to2);
    }
  }

  void drawWallSW(Point point, CardinalMatrix matrix) {
    //    Palette palette(kBlueMask, kWhiteMask);
    Palette palette(0xFFFF0000, kWhiteMask);
    Pen pen(logger, canvas, 2, false, palette);
    if (not matrix[CardinalMatrix::S] and not matrix[CardinalMatrix::W]) {
      pen.drawArc(point, kWallRadius * gridSize, 180_Degrees, 271_Degrees);
    }
    if (matrix[CardinalMatrix::S] and not matrix[CardinalMatrix::W]) {
      Point from(point.x + gridSize * -1 * kWallRadius, point.y);
      Point to(point.x + gridSize * -1 * kWallRadius, point.y + gridSize * 0.5 + 1);
      pen.drawLine(from, to);
    }
    if (not matrix[CardinalMatrix::S] and matrix[CardinalMatrix::W]) {
      Point from(point.x, point.y + gridSize * kWallRadius);
      Point to(point.x + gridSize * -0.5 - 1, point.y + gridSize * kWallRadius);
      pen.drawLine(from, to);
    }
    if (matrix[CardinalMatrix::S] and matrix[CardinalMatrix::W] and not matrix[CardinalMatrix::SW]) {
      Point outerPoint(point.x + gridSize * -2 * kWallRadius, point.y + gridSize * 2 * kWallRadius);
      pen.drawArc(outerPoint, kWallRadius * gridSize - 1, 0_Degrees, 91_Degrees);
      Point from1(point.x + gridSize * -2 * kWallRadius + 1, point.y + gridSize * kWallRadius);
      Point to1(point.x + gridSize * -0.5, point.y + gridSize * kWallRadius);
      pen.drawLine(from1, to1);
      Point from2(point.x + gridSize * -1 * kWallRadius, point.y + gridSize * 2 * kWallRadius - 1);
      Point to2(point.x + gridSize * kWallRadius, point.y + gridSize * 0.5);
      pen.drawLine(from2, to2);      
    }
  }

  void drawWallNW(Point point, CardinalMatrix matrix) {
    Palette palette(kBlueMask, kWhiteMask);
    Pen pen(logger, canvas, 2, false, palette);
    //    pen.debug(true);
    if (not matrix[CardinalMatrix::N] and not matrix[CardinalMatrix::W]) {
      pen.drawArc(point, kWallRadius * gridSize, 90_Degrees, 179_Degrees);
    }
    if (matrix[CardinalMatrix::N] and not matrix[CardinalMatrix::W]) {
      Point from(point.x + gridSize * kWallRadius, point.y);
      Point to(point.x + gridSize * -1 * kWallRadius, point.y + gridSize * -0.5 - 1);
      pen.drawLine(from, to);
    }
    if (not matrix[CardinalMatrix::N] and matrix[CardinalMatrix::W]) {
      Point from(point.x, point.y + gridSize * -1 * kWallRadius);
      Point to(point.x + gridSize * -0.5 - 1, point.y + gridSize * -1 * kWallRadius);
      pen.drawLine(from, to);
    }
    if (matrix[CardinalMatrix::N] and matrix[CardinalMatrix::W] and not matrix[CardinalMatrix::NW]) {
      Point outerPoint(point.x + gridSize * -2 * kWallRadius, point.y + gridSize * -2 * kWallRadius);
      pen.drawArc(outerPoint, kWallRadius * gridSize - 1, 270_Degrees, 361_Degrees);
      Point from1(point.x + gridSize * -2 * kWallRadius + 1, point.y + gridSize * -1 * kWallRadius);
      Point to1(point.x + gridSize * -0.5, point.y + gridSize * -1 * kWallRadius);
      pen.drawLine(from1, to1);
      Point from2(point.x + gridSize * -1 * kWallRadius, point.y + gridSize * -2 * kWallRadius + 1);
      Point to2(point.x + gridSize * -1 * kWallRadius, point.y + gridSize * -0.5);
      pen.drawLine(from2, to2);      
    }
  }

  void drawWalls(Grid walls) {
    for(CardinalMatrix matrix : walls) {
      Point projection(project(matrix.point()));
      logger << "point " << projection;
      if (matrix[CardinalMatrix::HERE]) {
	logger << matrix;
	drawWallNE(projection, matrix);
	drawWallSE(projection, matrix);
	drawWallSW(projection, matrix);
	drawWallNW(projection, matrix);
      }
    }
  }

  void drawFood() {
  }

  void drawCapsules() {
  }

  /*
  void draw(GameState state) {
    uint32_t* pixels = static_cast<uint32_t*>(pixelBuffer->data());
    if (!pixels) {
      return;
    }

    // Clear the buffer
    const int32_t height = pixelBuffer->size().height();
    const int32_t width = pixelBuffer->size().width();
    logger << "buffer height: " << height << " width: " << width;
    //  const float radius2 = (ball_rect_.width() / 2) * (ball_rect_.width() / 2);
    for (int32_t py = 0; py < height; ++py) {
      for (int32_t px = 0; px < width; ++px) {
	const int32_t pos = px + py * width;
	uint32_t color = kOpaqueColorMask;
	pixels[pos] = color;
      }
    }

    Palette palette(kWhiteMask, 0xFF0000FF);
    Pen p(logger, canvas, 12, true, palette);
    p.debug(true);
    //    p.drawArc(300, 300, 100, 240, 330);

    //    logger << "Second arc";
    //    p.drawArc(100, 100, 50, 0, 359);
    drawWalls(state.walls());
  }
  */
};

#endif//VIEW_H
