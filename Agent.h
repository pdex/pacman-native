// -*- C++ -*-
#ifndef AGENT_H
#define AGENT_H

#include "Direction.h"

class GameState;

class Agent {
public:
  virtual Direction getAction(GameState state) = 0;
  virtual void registerInitialState(GameState state) = 0;
};

#endif
