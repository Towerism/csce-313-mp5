#pragma once

#include <map>
#include <string>
#include <initializer_list>
#include <memory>
#include "bounded_buffer.h"
#include "data.h"

struct Buffer_filter {
  Buffer_filter();
  Buffer_filter(int buf_size, const std::initializer_list<std::string>& names);
  void push(const Data& d);
  Data pop(const std::string& name);
  Bounded_buffer<Data>* get(const std::string& name) { return buffers[name].get(); }
private:
  std::map<std::string, std::unique_ptr<Bounded_buffer<Data>>> buffers;
};
