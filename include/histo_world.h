#ifndef HISTO_WORLD_H
#define HISTO_WORLD_H
#include <vector>
#include <string>

#include "ascii-engine/include/ascii-engine/world.h"
//#include "entities/game_board.h"
#include "ascii-engine/include/ascii-engine/entity.h"
#include <memory>

namespace ae = ascii_engine;

struct HistoWorld : ae::World {
  HistoWorld(int x, int y, std::vector<std::string> names);
  virtual void update(double delta_time);
private:
  std::shared_ptr<ascii_engine::Entity> chart;
};

#endif // GAME_WORLD_H
