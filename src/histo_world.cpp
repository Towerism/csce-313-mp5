//#include "../lib/ascii-engine/include/ascii-engine/entities/test_entity.h"
#include "histo_world.h"
#include "histo_chart.h"
#include <memory>

using namespace std;

//based on ConnectFour
HistoWorld::HistoWorld(int x, int y, vector<string> names) :
  ascii_engine::World(200, 100), chart(new HistoChart(names)) {
    add(chart);
  }

void HistoWorld::update(double delta_time) {
  // do update stuff
  // call parent function
  ascii_engine::World::update(delta_time);
}
