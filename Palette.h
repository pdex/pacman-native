// -*- C++ -*-
#ifndef PALETTE_H
#define PALETTE_H

typedef uint32_t Color;

struct Palette {
  const Color outline;
  const Color fill;
  const Color debug;
  Palette(Color outline, Color fill, Color debug=0xFFFF0000)
    : outline(outline)
    , fill(fill)
    , debug(debug)
  {
  }
};

#endif//PALETTE_H
