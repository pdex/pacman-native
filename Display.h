// -*- C++ -*-
#ifndef DISPLAY_H
#define DISPLAY_H

#include <memory>
#include <ppapi/cpp/graphics_2d.h>
#include <ppapi/cpp/image_data.h>
#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/size.h>
#include "CanvasImageData.h"
#include "Logger.h"
#include "Pen.h"
#include "View.h"

/*
namespace {
  const uint32_t kOpaqueColorMask = 0xff000000;  // Opaque pixels.
  const uint32_t kWhiteMask = 0xffffff;
  const uint32_t kBlueMask = 0xFF0000FF;
  const double kWallRadius = 0.15;
}
*/

class Display {
  pp::Instance *instance;
  std::shared_ptr<Logger> logger;
  std::shared_ptr<pp::Graphics2D> context;
  std::shared_ptr<pp::ImageData> pixelBuffer;
  std::shared_ptr<Canvas> canvas;
  const int32_t width;
  const int32_t height;
  const int32_t gridSize;
  std::shared_ptr<View> view;

  bool flushPending;
public:
  Display(pp::Instance* instance, const pp::Size& size, std::shared_ptr<Logger> logger)
    : instance(instance)
    , logger(logger)
    , context(std::make_shared<pp::Graphics2D>(instance, size, false))
    , width(size.width())
    , height(size.height())
    , gridSize(30)
    , flushPending(false)
  {
    if (!instance->BindGraphics(*context)) {
      instance->PostMessage(pp::Var("ERROR: Couldn't bind the device context"));
    }
    if (context) {
      pixelBuffer = std::make_shared<pp::ImageData>(
        instance,
	PP_IMAGEDATAFORMAT_BGRA_PREMUL,
	context->size(),
	false
      );
      canvas = std::make_shared<CanvasImageData>(pixelBuffer);
      view = std::make_shared<View>(canvas, logger);
    }
    logger << "Size "
	   << " width: " << width
	   << "height: " << height
      ;
  }

  void update(GameState state) {
    draw(state);
    flush();
  }

  /*
  Point project(Point point) {
    return Point((point.x + 1) * gridSize, (point.y + 1) * gridSize);
  }
  
  void drawWallNE(Point point, CardinalMatrix matrix) {
    Palette palette(kBlueMask, kWhiteMask);
    Pen pen(logger, canvas, 4, false, palette);
    //    pen.debug(true);
    if (not matrix[CardinalMatrix::N] && not matrix[CardinalMatrix::E]) {
      pen.drawArc(point, kWallRadius * gridSize, 0_Degrees, 91_Degrees);
    }
    if (matrix[CardinalMatrix::N] && not matrix[CardinalMatrix::E]) {
      Point from(point.x + gridSize * kWallRadius, point.y);
      Point to(point.x + gridSize * kWallRadius, point.y+(gridSize * -0.5)-1);
      pen.drawLine(from, to);
    }
    if (not matrix[CardinalMatrix::N] && matrix[CardinalMatrix::E]) {
      Point from(point.x, point.y + gridSize * -1 * kWallRadius);
      Point to(point.x + (gridSize * -0.5)-1, point.y + gridSize * -1 * kWallRadius);
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
  }

  void drawWallSW(Point point, CardinalMatrix matrix) {
  }

  void drawWallNW(Point point, CardinalMatrix matrix) {
  }

  void drawWalls(Grid walls) {
    for(CardinalMatrix matrix : walls) {
      Point projection(project(matrix.point()));
      drawWallNE(projection, matrix);
  
      drawWallSE(projection, matrix);
      drawWallSW(projection, matrix);
      drawWallNW(projection, matrix);
  
    }
  }
*/
  void drawFood() {
  }

  void drawCapsules() {
  }
  
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
    view->drawWalls(state.walls());
  }

  static void callback(void* data, int32_t result) {
    static_cast<Display*>(data)->flushComplete();
  }
  
  void flush() {
    if (!context) {
      return;
    }
    
    context->PaintImageData(*pixelBuffer, pp::Point());
    if (flushPending) {
      return;
    }
    flushPending = true;
    context->Flush(pp::CompletionCallback(&Display::callback, this));
  }

  void flushComplete() {
    flushPending = false;
  }
};

#endif//DISPLAY_H
