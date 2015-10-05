// -*- C++ -*-
#ifndef LOOPER_H
#define LOOPER_H

#include <functional>
#include <queue>
#include <ppapi/cpp/module.h>
#include <ppapi/cpp/completion_callback.h>

typedef std::queue<std::function<void()>> Events;

class Looper {
  int32_t updateInterval;
  Events events;
  
public:
  Looper(int32_t updateInterval)
    : updateInterval(updateInterval)
  {
  }

  void schedule(std::function<void()> function) {
    events.push(function);

    pp::Core* core = pp::Module::Get()->core();
    pp::CompletionCallback callback(Looper::callback, this);
    core->CallOnMainThread(updateInterval, callback);
  }

  static void callback(void* data, int32_t /*result*/) {
    Looper* looper = static_cast<Looper*>(data);

    if (looper->events.size()) {
      std::function<void()> function = looper->events.front();
      function();
      looper->events.pop();
    }
  }
};

#endif//LOOPER_H
