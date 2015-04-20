#include "histo_chart.h"
#include <iostream>
using namespace std;

string multiplyStringBy(string original, int times);
string makeNamesRow( vector<string> client_names);

void HistoChart::update(double delta_time) {
    // do update stuff
    set_graphic(generateChart());
    //clears rows variable before update
    deleteRows();
    // call parent function
    ascii_engine::Entity::update(delta_time);
  }

HistoChart::HistoChart() : ascii_engine::Entity(5, 5){
}
string HistoChart::generateChart(){
  string chart = "";
  vector<string> client_names;
  for(int i = 0; i < clients.size(); i++){
    client_names.push_back(clients[i]->client_name);
  }
  populateRows(client_names);
  for(string r: rows) {
    chart += r;
  }
  return chart;
}

void HistoChart::deleteRows(){
  rows.clear();
}

void HistoChart::populateRows(vector<string> client_names){

  string empty_row = multiplyStringBy("|" + multiplyStringBy(" ", size_of_bar)+ "|", client_names.size()) + "\n";
  string filled_row = multiplyStringBy("|" + multiplyStringBy("=", size_of_bar) + "|", client_names.size()) + "\n";

  string x_names = makeNamesRow(client_names);

  int height = 21;
  int current_thresh = 1;
  int last_thresh = 1;
  for(int i = 0; i < height; i++){
    string row = "";

    //such hackery. Refactor.
    string stats_row =  makeStatsRow(i / 2);

    if(i % 2 == 0){
      current_thresh = (i + 2) * 5;
      string y_label = "";
      if(current_thresh > 100){
        y_label += "Total ";
      }
      else{
        y_label += to_string(last_thresh) + "-" + to_string(current_thresh);
      }
      string padding = multiplyStringBy(" ", 6 - y_label.size());
      row += padding + y_label;
      row += stats_row;
    }
    else {
      row += "      ";
      row += empty_row;
    }
    rows.push_back(row);
    last_thresh = current_thresh + 1;
  }

  rows.insert(rows.begin(), "      " + filled_row);
  rows.insert(rows.begin(), x_names);
  rows.insert(rows.begin(), "Press q to exit display\n\n\n");
}

string multiplyStringBy(string original, int times){
  string result = "";
  for(int i = 0; i < times; i++){
    result += original;
  }
  return result;
}

string makeNamesRow( vector<string> client_names){
  string x_names = "Range: ";
  for(string c : client_names){
    x_names += "           " + c + multiplyStringBy(" ", 15);
  }
  x_names += "\n";
  return x_names;
}
//for row 11, print the sums
string HistoChart::makeStatsRow(int row){
  string stats_row = "";
  for(int j = 0; j < clients.size(); j++){
    string one_row = "";
    one_row += "|" + multiplyStringBy(" ", 10);
    if(row == 10){
      one_row += to_string(clients[j]->sumOfStats());
    }
    else{
        one_row += to_string(clients[j]->client_stats[row]);
    }
    one_row += multiplyStringBy(" ", (size_of_bar+1) - one_row.size());
    one_row += "|";
    stats_row += one_row;
  }
  stats_row += "\n";
  return stats_row;
}

