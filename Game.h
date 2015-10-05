// -*- C++ -*-
#ifndef GAME_H
#define GAME_H

#include <functional>

#include "Looper.h"
#include "GameState.h"
#include "Action.h"
#include "Agents.h"
#include "Agent.h"
#include "Direction.h"
#include "Display.h"
#include "Rules.h"

class Game {
  Looper looper;
  GameState state;
  Agents agents;
  Display display;
  Rules rules;
  int agentIndex;
  bool gameOver;

  void initAgents() {
    for(auto agent : agents) {
      agent->registerInitialState(state);
    };
  }

  void iterateLoop() {
    if (gameOver) {
      return;
    }

    std::function<void()> f = [this] () {
      this->iterateLoop();
    };
    //looper.schedule(f);

    // Fetch the next agent
    //auto agent = agents[agentIndex];

    // Duplicate state
    //GameState observation(state);
  
    // Solicit an action
    //Direction action = agent->getAction(observation);

    // Execute the action
    //state = state.generateSuccessor(agentIndex, action);

    // Change the display
    display.update(state);

    /*
    // Allow for game specific conditions (winning, losing, etc.)
    rules.process(state, this);
    */
  
    // Next agent
    //agentIndex = ( agentIndex + 1 ) % agents.size();
    agentIndex = 0;
  }
public:
  Game(Looper looper, GameState state, Agents agents, Display display, Rules rules)
    : looper(looper)
    , state(state)
    , agents(agents)
    , display(display)
    , rules(rules)
    , agentIndex(0)
    , gameOver(false)
  {
  }
  
  void run() {
    //initAgents();
    iterateLoop();
  }
};

#endif//GAME_H
