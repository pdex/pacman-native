// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <ppapi/cpp/instance.h>
#include "ppapi/cpp/module.h"
#include <ppapi/cpp/size.h>
#include "ppapi/cpp/var.h"

#include "Game.h"
#include "LayoutBuilder.h"
#include "Logger.h"
#include "LoggerPostMessage.h"

namespace {

// The expected string sent by the browser.
const char* const kHelloString = "hello";
// The string sent back to the browser upon receipt of a message
// containing "hello".
const char* const kReplyString = "hello from NaCl";

}  // namespace

class HelloTutorialInstance : public pp::Instance {
  std::shared_ptr<Logger> logger;
  std::string layStr = std::string(R"EOF(
%%%%%%%%%%%%%%%%%%%%
%......%G  G%......%
%.%%...%%  %%...%%.%
%.%o.%........%.o%.%
%.%%.%.%%%%%%.%.%%.%
%........P.........%
%%%%%%%%%%%%%%%%%%%%)EOF").substr(1);
  AgentFactory factory;
  Layout layout;
  pp::Size size;
  Display display;
  Rules rules;
  Game game;
 public:
  explicit HelloTutorialInstance(PP_Instance instance)
      : pp::Instance(instance)
      , logger(std::make_shared<LoggerPostMessage>(this))
      , layout(LayoutBuilder::parse(layStr, factory, logger))
      , size(800, 600)
      , display(this, size, logger)
      , game(
	     Looper(12),
	     GameState(layout),
	     layout.getAgents(),
	     display,
	     rules
      )
      {
      }
  virtual ~HelloTutorialInstance() {}

  virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]) {
    try {
      game.run();
    } catch (const std::exception &e) {
      PostMessage(std::string("Exception: ") + e.what());
    } catch (...) {
      PostMessage("A turrible exception were thrown");
    }
    return true;
  }

  virtual void HandleMessage(const pp::Var& var_message) {
    // Ignore the message if it is not a string.
    if (!var_message.is_string())
      return;

    // Get the string message and compare it to "hello".
    std::string message = var_message.AsString();
    if (message == kHelloString) {
      // If it matches, send our response back to JavaScript.
      pp::Var var_reply(kReplyString);
      PostMessage(var_reply);
    }
  }
};

class HelloTutorialModule : public pp::Module {
 public:
  HelloTutorialModule() : pp::Module() {}
  virtual ~HelloTutorialModule() {}

  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new HelloTutorialInstance(instance);
  }
};

namespace pp {

Module* CreateModule() {
  return new HelloTutorialModule();
}

}  // namespace pp
