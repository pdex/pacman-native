// -*- C++ -*-
#ifndef CANVAS_H
#define CANVAS_H

#include <cstdint>

class Canvas {
  uint32_t* pixels;
  const int32_t width;
  const int32_t height;
public:
  Canvas(uint32_t *pixels, int32_t width, int32_t height)
    : pixels(pixels)
    , width(width)
    , height(height)
  {
  }
  
  void putpixel(int x, int y, int color) {
    if (x < 0 || x >= width) {
      return;
    }

    if (y < 0 || y >= height) {
      return;
    }
    
    const int32_t pos = x + y * width;
    pixels[pos] = color;
  }  
};

#endif//CANVAS_H
