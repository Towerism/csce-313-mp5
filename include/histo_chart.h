#ifndef HISTO_CHART_H
#define HISTO_CHART_H
#include <algorithm>
#include <vector>
#include <string>
#include "histo_client.h"
#include "../lib/ascii-engine/include/ascii-engine/entity.h"


struct HistoChart : ascii_engine::Entity {
  HistoChart();
  string generateChart();
  void deleteRows();
  void populateRows(std::vector<string> client_names);
  string makeStatsRow(int row);
  void addClient(HistoClient * client){clients.push_back(client);}


  virtual void update(double delta_time) override;

  int size_of_bar = 30; //padding
  std::vector<string> rows; //bottom-to-top. Lowest rows are the smallest
  std::vector<HistoClient *> clients;
};

#endif
