//#include "../lib/ascii-engine/include/ascii-engine/entities/test_entity.h"
#include "histo_world.h"
#include "histo_chart.h"
#include <memory>

using namespace std;

//based on ConnectFour
HistoWorld::HistoWorld() :
  ascii_engine::World(200, 100), chart(new HistoChart()) {
    add(chart);
  }

