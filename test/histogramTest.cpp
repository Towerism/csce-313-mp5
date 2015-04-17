#include <gtest/gtest.h>
#include <memory>
#include "histo_world.h"
#include "ascii-engine/include/ascii-engine/engine.h"

TEST(HistogramTest, Generate) {
  //EXPECT_EQ(1,1);
  ascii_engine::Engine engine(60);
  engine.set_world(std::shared_ptr<ae::World>(new HistoWorld(100, 100)));
  engine.game_loop();
}
