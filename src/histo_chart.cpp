#include "histo_chart.h"
#include <iostream>
using namespace std;

string multiplyStringBy(string original, int times);
HistoChart::HistoChart(vector<string> client) : ascii_engine::Entity(5, 5) {
  set_graphic(generateStartingChart(client));
}
string HistoChart::generateStartingChart(vector<string> client){
  int size_of_bar = 20; //padding
  string x_label_offset = "    ";
  string empty_row = multiplyStringBy("|" + multiplyStringBy(" ", size_of_bar)+ "|", client.size()) + "\n";
  string filled_row = multiplyStringBy("|" + multiplyStringBy("=", size_of_bar) + "|", client.size()) + "\n";
  string x_labels = x_label_offset;
  for(string c : client){
    x_labels += c + multiplyStringBy(" ", 2 + size_of_bar - c.size());
  }
  int height = 20;
  int player_score = 0;

  for(int i = 0; i < height; i++){
    string row = "";
    int y = i * 5;
    if(i % 2 == 0){
      string padding = multiplyStringBy(" ", 4 - to_string(y).size());
      row += padding + to_string(y);
    }
    else {
      row += "    ";
    }
    if(player_score < y){
        row += empty_row;
    }
    else{
      row += filled_row;
    }
    rows.insert(rows.begin(), row);
  }

  rows.push_back(x_labels);
  //rows.push_back(x_labels);
  //should be it's own fctn
  string chart = "";
  for(string r: rows) {
    chart += r;
  }
  return chart;
}

string multiplyStringBy(string original, int times){
  string result = "";
  for(int i = 0; i < times; i++){
    result += original;
  }
  return result;
}
//string increase
