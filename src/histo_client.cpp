#include "histo_client.h"

void HistoClient::addData(int d){
  if(((d/10) < 10) && ((d/10) >= 0)){
    client_stats[d/10] += 1;
  }
  else{
    //std::cout << "Data is out of range... \n" << std::endl;
  }
}
int HistoClient::sumOfStats(){
  int sum = 0;
  for(int stat : client_stats){
    sum += stat;
  }
  return sum;
}

inline bool is_integer(std::string & s);

void HistoClient::run() {
  while(true){
    Data d = buffer.dequeue();
    int x  = 0; //NOTE: if the total is incorrect, this is happening
    if(is_integer(d.data)){
        int x = std::stoi(d.data);
    }
    else{
      //std::cout << "Data is not in the proper format. exhibit a: " << d.data << std::endl;
    }
    addData(x);
  }
}
//from stackoverflow..a very common function
inline bool is_integer(std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   std::strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}
