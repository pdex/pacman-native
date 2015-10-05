// -*- C++ -*-
#ifndef LAYOUT_BUILDER_H
#define LAYOUT_BUILDER_H

#include <vector>
#include "AgentFactory.h"
#include "Agents.h"
#include "Grid.h"
#include "Layout.h"
#include "Logger.h"
#include "Point.h"

class LayoutBuilder {
  std::shared_ptr<Logger> logger;
  AgentFactory factory;
  int8_t width;
  int8_t height;
  std::vector<std::string> rows;
  Grid walls;
  Grid food;
  std::vector<Point> capsules;
  Agents agents;

  void splitRows(std::string text) {
    size_t current;
    size_t next = -1;
    do {
      current = next + 1;
      next = text.find_first_of("\n", current);
      rows.push_back(text.substr(current, next - current));
    } while (next != std::string::npos);
    width = rows[0].size();
    height = rows.size();
    walls = Grid(width, height, false);
    food = Grid(width, height, false);
  }
  
  /*
    The shape of the maze.  Each character
    represents a different type of object.
     % - Wall
     . - Food
     o - Capsule
     G - Ghost
     P - Pacman
    Other characters are ignored.
   */
  void processLayoutChar(int x, int y, char ch) {
    switch(ch) {
      case '%':
	walls[x][y] = true;
        break;
      case '.':
	food[x][y] = true;
	break;
      case 'o':
	//	capsules.push_back(Point(x,y));
        break;
      case 'P':
	//	agents.push_back(factory(0));
        break;
      case 'G':
      case '1':
	//	agents.push_back(factory(1));
        break;
      case '2':
	//	agents.push_back(factory(2));
        break;
      case '3':
	//	agents.push_back(factory(3));
        break;
      case '4':
	//	agents.push_back(factory(4));
        break;
    }
  }

  void processLayoutText() {
    int y = 0;
    for(std::string row : rows) {
      logger << row;
      int x = 0;
      for(char ch : row) {
	processLayoutChar(x, y, ch);
	x++;
      }
      y++;
    }
  }

  Layout build(std::string text) {
    splitRows(text);
    processLayoutText();

    logger << "Width: " << int32_t(width) << " Height: " << int32_t(height);
    return Layout(
      text,
      width,
      height,
      walls,
      food,
      capsules,
      agents
    );
  }
public:
  LayoutBuilder(std::shared_ptr<Logger> logger, AgentFactory factory)
    : logger(logger)
    , factory(factory)
  {
  }
  static Layout parse(std::string text, AgentFactory factory, std::shared_ptr<Logger> logger) {
    LayoutBuilder builder(logger, factory);
    return builder.build(text);
  }
};

#endif//LAYOUT_BUILDER_H
