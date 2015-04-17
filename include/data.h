#pragma once

#include <string>

struct Data {
  Data() { }
  Data(const std::string& origin, const std::string& data) : request_origin(origin), data(data) { }
  std::string request_origin; // name of the client who started the request
  std::string data;
};
