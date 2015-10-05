// -*- C++ -*-
#ifndef LOGGER_NULL_H
#define LOGGER_NULL_H

#include "Logger.h"

class LoggerNull : public Logger {
  class Builder : public Logger::Builder {
  public:
    virtual ~Builder() {}
  };
public:
  virtual BuilderPtr createBuilder() {
    return std::make_shared<LoggerNull::Builder>();
  }
  
  LoggerNull() {
  }
};

#endif//LOGGER_NULL_H
