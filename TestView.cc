#include "View.h"
#include <gtest/gtest.h>
#include "LayoutBuilder.h"
#include "LoggerNull.h"

TEST(ViewTest, DrawWalls) {
  Grid grid(20, 7, false);
  std::string layStr = std::string(R"EOF(
%%%%%%%%%%%%%%%%%%%%
%......%G  G%......%
%.%%...%%  %%...%%.%
%.%o.%........%.o%.%
%.%%.%.%%%%%%.%.%%.%
%........P.........%
%%%%%%%%%%%%%%%%%%%%)EOF").substr(1);
  AgentFactory factory;
  std::shared_ptr<Logger> logger(std::make_shared<LoggerNull>());
  Layout layout(LayoutBuilder::parse(layStr, factory, logger));
  GameState state(layout);
  int32_t width = 800;
  int32_t height = 600;
  uint32_t *pixels = new uint32_t[width*height];
  std::shared_ptr<Canvas> canvas(std::make_shared<Canvas>(pixels, width, height));
  View view(canvas, logger);
  view.drawWalls(state.walls());
}
