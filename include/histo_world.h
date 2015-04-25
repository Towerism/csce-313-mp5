#ifndef HISTO_WORLD_H
#define HISTO_WORLD_H
#include <vector>
#include <string>

#include "ascii-engine/world.h"
#include "ascii-engine/entity.h"
#include <memory>
#include "histo_chart.h"

namespace ae = ascii_engine;

struct HistoWorld : ae::World {
  HistoWorld();

  void addClient(HistoClient * client){chart->addClient(client);}
  int getClients(){return chart->clients.size();}

private:
  std::shared_ptr<HistoChart> chart;
};

#endif // GAME_WORLD_H
