#ifndef HISTO_CLIENT_H
#define HISTO_CLIENT_H
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "runnable.h"
#include "bounded_buffer.h"

struct HistoClient : public Runnable {
 HistoClient(std::string name, Bounded_buffer<int>& buf) : client_name(name), buffer(buf), client_stats(10, 0){}

  //add a single datum at a time
  void addData(int d);
  int sumOfStats();
  virtual void run() override;

  //member variables
  std::string client_name;
  Bounded_buffer<int>& buffer;
  std::vector<int> client_stats;
};



#endif
