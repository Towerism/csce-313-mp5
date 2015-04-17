#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <string>
#include "histo_world.h"
#include "ascii-engine/include/ascii-engine/engine.h"

TEST(HistogramTest, Generate) {
  ascii_engine::Engine engine(60);
  std::vector<std::string> names = {"Joe Smith", "Jane Smith", "John Doe"};
  engine.set_world(std::shared_ptr<ae::World>(new HistoWorld(200, 100, names)));
  engine.game_loop();
}

TEST(HistogramTest, Add) {
  EXPECT_EQ(1,1);
}
