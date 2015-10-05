// -*- C++ -*-
#ifndef AGENT_FACTORY_H
#define AGENT_FACTORY_H

#include "Agent.h"

class AgentFactory {
public:
  AgentFactory() {
  }
  std::shared_ptr<Agent> operator()(int idx) {
    return std::shared_ptr<Agent>();
  }
};

#endif//AGENT_FACTORY_H
