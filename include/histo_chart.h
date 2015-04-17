#ifndef HISTO_CHART_H
#define HISTO_CHART_H
#include <algorithm>
#include <string>
#include "../lib/ascii-engine/include/ascii-engine/entity.h"


struct HistoChart : ascii_engine::Entity {
  HistoChart(std::vector<string> players);
  std::vector<string> rows; //bottom-to-top. Lowest rows are the smallest
  string generateStartingChart(std::vector<string> client);
};

#endif
