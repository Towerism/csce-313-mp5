#ifndef HISTO_CHART_H
#define HISTO_CHART_H
#include <algorithm>
#include <vector>
#include <string>
#include "histo_client.h"
#include "../lib/ascii-engine/include/ascii-engine/entity.h"


struct HistoChart : ascii_engine::Entity {
  HistoChart(std::vector<string> client_names);
  string generateStartingChart(std::vector<string> client_names);
  void populateRows(std::vector<string> client_names);

  std::vector<string> rows; //bottom-to-top. Lowest rows are the smallest
  std::vector<HistoClient> stats;
};

#endif
