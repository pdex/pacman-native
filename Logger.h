// -*- C++ -*-
#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <sstream>

class Logger {
public:
  class Builder;
  typedef std::shared_ptr<Builder> BuilderPtr;
  class Builder {
    std::stringstream buffer;
  public:
    std::string message() {
      return buffer.str() + "\n";
    }

    virtual ~Builder() {}

    template<typename T>
    Builder& operator<<(T message) {
      buffer << message;
      return *this;
    }

    template<typename T>
    friend BuilderPtr operator<<(BuilderPtr builder, T message) {
      *builder << message;
      return builder;
    }
  };

  virtual BuilderPtr createBuilder() = 0;

  template<typename T>
  friend BuilderPtr operator<<(std::shared_ptr<Logger> logger, T message) {
    BuilderPtr builder(logger->createBuilder());
    builder << message;
    return builder;
  }
};

#endif//LOGGER_H
