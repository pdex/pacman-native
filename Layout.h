// -*- C++ -*-
#ifndef LAYOUT_H
#define LAYOUT_H

#include "Agents.h"
#include "Grid.h"
#include "Point.h"

class Layout {
  std::string text;
  int8_t width;
  int8_t height;
  Grid walls;
  Grid food;
  std::vector<Point> capsules;
  Agents agents;
public:
  Layout() {}
  Layout(std::string text, int8_t width, int8_t height, Grid walls, Grid food, std::vector<Point> capsules, Agents agents)
    : text(text)
    , width(width)
    , height(height)
    , walls(walls)
    , food(food)
    , capsules(capsules)
    , agents(agents)
  {
  }
  Agents getAgents() { return agents; }
  Grid getWalls() { return walls; }
};

#endif//LAYOUT_H
