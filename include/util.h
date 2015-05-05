#ifndef UTIL_H
#define UTIL_H

#include <cstring>
#include <string>

bool is_number(const std::string& str) {
  if(str.empty()){
    return false;
  }
  const char* s = str.c_str();
  char* p = nullptr;
  long converted = strtol(s, &p, 10);
  if (*p) {
    return false;
  }
  return true;
}

#endif // UTIL_H
