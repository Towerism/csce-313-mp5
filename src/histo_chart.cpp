#include "histo_chart.h"
#include <iostream>
using namespace std;

string multiplyStringBy(string original, int times);
string makeNamesRow( vector<string> client_names);

HistoChart::HistoChart(vector<string> client_names) : ascii_engine::Entity(5, 5){
  for( int i =0; i < client_names.size(); ++i){
    stats.push_back(client_names[i]);
  }
  set_graphic(generateStartingChart(client_names));
}
string HistoChart::generateStartingChart(vector<string> client_names){
  //should be it's own fctn
  string chart = "";
  populateRows(client_names);
  for(string r: rows) {
    chart += r;
  }
  return chart;
}

void HistoChart::populateRows(vector<string> client_names){
  int size_of_bar = 40; //padding

  string empty_row = multiplyStringBy("|" + multiplyStringBy(" ", size_of_bar)+ "|", client_names.size()) + "\n";
  string filled_row = multiplyStringBy("|" + multiplyStringBy("=", size_of_bar) + "|", client_names.size()) + "\n";

  string x_names = makeNamesRow(client_names);

  int height = 21;
  int player_score = 0;
  int current_thresh = 1;
  int last_thresh = 1;
  for(int i = 2; i < height; i++){
    string row = "";

    if(i % 2 == 0){
      current_thresh = (i * 5);
      string y_label = to_string(last_thresh) + "-" + to_string(current_thresh);
      string padding = multiplyStringBy(" ", 6 - y_label.size());
      row += padding + y_label;
    }
    else {
      row += "      ";
    }
    row += empty_row;
    rows.insert(rows.begin(), row);
    last_thresh = current_thresh + 1;
  }

  rows.insert(rows.begin(), "      " + filled_row);
  rows.insert(rows.begin(), x_names);
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
    x_names += "        " + c + multiplyStringBy(" ", 25);
  }
  x_names += "\n";
  return x_names;
}
