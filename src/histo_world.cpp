//#include "../lib/ascii-engine/include/ascii-engine/entities/test_entity.h"
#include "histo_world.h"
#include "histo_chart.h"
#include <memory>
#include <vector>
#include <string>

using namespace std;

//based on ConnectFour
HistoWorld::HistoWorld(int x, int y) :
  ascii_engine::World(x, y), chart(new HistoChart(std::vector<string>{"Joe Smith", "Jane Smith", "John Doe"})) {
    add(chart);
  }

void HistoWorld::update(double delta_time) {
  // do update stuff
  // call parent function
  ascii_engine::World::update(delta_time);
}
