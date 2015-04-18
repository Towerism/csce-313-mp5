#include "histo_client.h"

void HistoClient::addData(int d){
  if(((d/10) < 10) && ((d/10) >= 0)){
    client_stats[d/10] += 1;
  }
  else{
    std::cout << "Data is out of range... \n" << std::endl;
  }
}
int HistoClient::sumOfStats(){
  int sum = 0;
  for(int stat : client_stats){
    sum += stat;
  }
  return sum;
}

void HistoClient::run() {
  while(true){
      buffer.dequeue();
    }
}
