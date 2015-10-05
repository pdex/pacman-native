// -*- C++ -*-
#ifndef PEN_H
#define PEN_H

#include <experimental/optional>
#include <memory>
#include "Canvas.h"
#include "Logger.h"
#include "Palette.h"
#include "Point.h"
#include "Radians.h"
#include "Rectangle.h"
#include "Trig.h"

typedef uint32_t Radius;

class Pen {
  std::shared_ptr<Logger> logger;
  std::shared_ptr<Canvas> canvas;
  const uint32_t width;
  const bool fill;
  Palette palette;
  bool drawDebug;
public:
  Pen(std::shared_ptr<Logger> logger, std::shared_ptr<Canvas> canvas, uint32_t width, bool fill, Palette palette)
    : logger(logger)
    , canvas(canvas)
    , width(width)
    , fill(fill)
    , palette(palette)
    , drawDebug(false)
  {
  }
  void debug(bool debug) {
    drawDebug = debug;
  }

  void drawLine(Point from, Point to) {
    int32_t deltax = from.x - to.x;
    int32_t deltay = from.y - to.y;
    int32_t xstep = (deltax < 0) ? 1 : -1;
    int32_t ystep = (deltay < 0) ? 1 : -1;
    if (deltax == 0) {
      for (int32_t y = from.y; y != (to.y + ystep); y += ystep) {
	canvas->putpixel(from.x, y, palette.outline);
      }
      return;
    }
    double error = 0;
    double deltaerror = std::abs(deltay / double(deltax));
    int32_t y = from.y;
    for (int32_t x = from.x; x != (to.x + xstep); x += xstep) {
      canvas->putpixel(x, y, palette.outline);
      error += deltaerror;
      while (error >= 0.5) {
	canvas->putpixel(x, y, palette.outline);
	y += ystep;
	error -= 1.0;
      }
    }
  }

  void drawArc(Point point, int32_t r, Degrees begin, Degrees end) {
    drawArc(point.x, point.y, r, begin, end);
  }

  void drawArc(int32_t px, int32_t py, int32_t r, Degrees begin, Degrees end) {
    if (begin >= end) {
      return;
    }

    Point origin(px, py);
    int radius = r + width/2;
    if ((begin < 90)) { // top right
      Point start = Trig::hypotenuse(origin, radius, begin);
      Point stop = Trig::hypotenuse(origin, radius, (end >= 90) ? 89_Degrees : end);
      //      logger << "Drawing top right " << stop.x << ", " << stop.y << " " << start.x << ", " << start.y;
      //      Rectangle clipping(stop, start);
      Rectangle clipping(Point(origin.x, origin.y-radius), Point(origin.x+radius, origin.y));
      shutup(origin, r, clipping, start, stop);
    }
    if ((begin < 180) && (end >= 90)) { // top left
      Point start = Trig::hypotenuse(origin, radius, (begin < 90) ? 90_Degrees : begin);
      Point stop = Trig::hypotenuse(origin, radius, (end >= 180) ? 180_Degrees : end); 
      //      logger << "Drawing top left " << stop.x << ", " << start.y << " " << start.x << ", " << stop.y;
      //      Rectangle clipping(Point(stop.x, start.y), Point(start.x, stop.y));
      Rectangle clipping(Point(origin.x-radius, origin.y-radius), origin);
      shutup(origin, r, clipping, start, stop);
    }
    if ((begin < 270) && (end >= 180)) { // bottom left
      Point start = Trig::hypotenuse(origin, radius, (begin < 180) ? 180_Degrees : begin);
      Point stop = Trig::hypotenuse(origin, radius, (end >= 270) ? 270_Degrees : end); 
      //      logger << "Drawing bottom left " << start.x << ", " << start.y << " " << stop.x << ", " << stop.y;
      //      Rectangle clipping(start, stop);
      Rectangle clipping(Point(origin.x-radius, origin.y), Point(origin.x, origin.y+radius));
      shutup(origin, r, clipping, start, stop);
    }
    if ((begin < 360) && (end >= 270)) { // bottom right
      Point start = Trig::hypotenuse(origin, radius, (begin < 270) ? 270_Degrees : begin);
      Point stop = Trig::hypotenuse(origin, radius, (end >= 360) ? 359_Degrees : end); 
      //      logger << "Drawing bottom right " << start.x << ", " << stop.y << " " << stop.x << ", " << start.y;
      //      Rectangle clipping(Point(start.x, stop.y), Point(stop.x, start.y));
      Rectangle clipping(origin, Point(origin.x+radius, origin.y+radius));
      //      logger << "Drawing bottom right " << origin.x << ", " << origin.y << " " << origin.x+radius << ", " << origin.y+radius;
      shutup(origin, r, clipping, start, stop);
    }
  }

  int32_t yintpoints(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4) {
    return ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4))
           /
           ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4))
    ;
  }

  int32_t xintpoints(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4) {
    return ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4))
           /
           ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4))
    ;
  }

  int32_t yint(Point origin, Point end, Point cross1, Point cross2) {
    return yintpoints(origin.x, origin.y, end.x, end.y, cross1.x, cross1.y, cross2.x, cross2.y);
  }

  std::experimental::optional<int32_t> xint(Point origin, Point end, Point cross1, Point cross2) {
    if (origin.y == end.y && cross1.y == cross2.y) {
      return std::experimental::optional<int32_t>();
    }
    if (origin.x == end.x && cross1.x == cross2.x) {
      return std::experimental::optional<int32_t>();
    }
    if (origin.x == end.x && origin.y == end.y) {
      return std::experimental::optional<int32_t>();
    }
    if (cross1.x == cross2.x && cross1.y == cross2.y) {
      return std::experimental::optional<int32_t>();
    }

    return xintpoints(origin.x, origin.y, end.x, end.y, cross1.x, cross1.y, cross2.x, cross2.y);
  }

  void shutup(Point origin, Radius r, Rectangle clipping, Point start, Point stop) {
    Point topLeft(std::min(start.x, stop.x), std::min(start.y, stop.y));
    Point bottomRight(std::max(start.x, stop.x), std::max(start.y, stop.y));
    Point runFrom = (start.x < stop.x) ? start : stop;
    Point runTo = (start.x > stop.x) ? start : stop;
    Rectangle clipping2(topLeft, bottomRight);
    //    logger << "run From " << runFrom << " run to " << runTo;
    for (int y=clipping.topLeft.y; y<=clipping.bottomRight.y; y++) {
      /*
      int32_t left = (origin.y == runFrom.y) ? clipping.topLeft.x : xOnLine(y, runFrom, origin);
      int32_t right = (origin.y == runTo.y) ? clipping.bottomRight.x : xOnLine(y, runTo, origin);
      */
      int32_t left = std::max(clipping.topLeft.x, xint(origin, runFrom, Point(topLeft.x, y), Point(bottomRight.x, y)).value_or(clipping.topLeft.x));
      int32_t right = std::min(clipping.bottomRight.x, xint(origin, runTo, Point(topLeft.x, y), Point(bottomRight.x, y)).value_or(clipping.bottomRight.x));
      //      for (int x=clipping.topLeft.x; x<=clipping.bottomRight.x; x++) {
      for (int x=left; x<=right; x++) {
	int xdist = abs(x-origin.x);
	int ydist = abs(y-origin.y);
	int hir = r+(width/2); hir *= hir;
	int lor = r-(width/2); lor *= lor;
	int distance = xdist*xdist+ydist*ydist;

	if ( (distance > lor) && (distance < hir) ) {
	  /*
	  logger << "Putting pixel x: " << x << " y: " << y
		 << " distance: " << distance
		 << " xdist: " << xdist
		 << " ydist: " << ydist
		 << " hir: " << hir
		 << " lor: " << lor
	  ;
	  */
	  canvas->putpixel(x, y, palette.outline);
	} else if (fill && (distance <= lor)) {
	  canvas->putpixel(x, y, palette.fill);
	} else if (drawDebug && (distance >= hir)) {
	  canvas->putpixel(x, y, palette.debug);
	}
      }
    }
  }
  
  void drawCircle(int32_t px, int32_t py, int32_t r) {
    int radius = r + width;
    for(int x=px-radius; x<=px+radius; x++) {
      for(int y=py-radius; y<=py+radius; y++) {
	int xdist = abs(x-px);
	int ydist = abs(y-px);
	int hir = r+(width/2); hir *= hir;
	int lor = r-(width/2); lor *= lor;
	int distance = xdist*xdist+ydist*ydist;

	if ( (distance > lor) && (distance < hir) ) {
	  /*
	  logger << "Putting pixel x: " << x << " y: " << y
		 << " distance: " << distance
		 << " xdist: " << xdist
		 << " ydist: " << ydist
		 << " hir: " << hir
		 << " lor: " << lor
	  ;
	  */
	  canvas->putpixel(x, y, palette.outline);
	} else if (fill && (distance <= lor)) {
	  canvas->putpixel(x, y, palette.fill);
	} else if (drawDebug && (distance >= hir)) {
	  canvas->putpixel(x, y, palette.debug);
	}
      }
    }
  }

    /*
  void drawPie(Rect rect, uint32_t radius) {
    uint32_t r;
    for(int x=px-radius; x<=px+radius; x++) {
      for(int y=py-radius; y<=py+radius; y++) {
	int xdist = abs(x-px);
	int ydist = abs(y-px);
	int hir = r+(width/2); hir *= hir;
	int lor = r-(width/2); lor *= lor;
	int distance = xdist*xdist+ydist*ydist;

	if ( (distance > lor) && (distance < hir) ) {
	  canvas->putpixel(x, y, palette.outline);
	} else if (fill && (distance <= lor)) {
	  canvas->putpixel(x, y, palette.fill);
	} else if (drawDebug && (distance >= hir)) {
	  canvas->putpixel(x, y, palette.debug);
	}
      }
    }
  }
    */
};

#endif//PEN_H
