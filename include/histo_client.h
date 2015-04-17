#ifndef HISTO_CLIENT_H
#define HISTO_CLIENT_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

struct HistoClient {
HistoClient(std::string name) : client_name(name), client_stats(10, 0){}

  //add a single datum at a time
  void addData(int d);
  int sumOfStats();

  std::string client_name;
  std::vector<int> client_stats;
};



#endif
