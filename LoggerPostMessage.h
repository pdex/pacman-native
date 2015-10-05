// -*- C++ -*-
#ifndef LOGGER_POST_MESSAGE_H
#define LOGGER_POST_MESSAGE_H

#include <ppapi/cpp/instance.h>
#include "Logger.h"

class LoggerPostMessage : public Logger {
  pp::Instance* instance;
  class Builder : public Logger::Builder {
    pp::Instance* instance;
  public:
    Builder(pp::Instance *instance) : instance(instance) {
    }

    virtual ~Builder() {
      instance->PostMessage(message());
    }
  };
public:
  LoggerPostMessage(pp::Instance* instance) : instance(instance) {
  }

  virtual BuilderPtr createBuilder() {
    return std::make_shared<LoggerPostMessage::Builder>(instance);
  }
};

#endif//LOGGER_POST_MESSAGE_H
