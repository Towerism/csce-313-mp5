#include <memory>
#include "buffer_filter.h"

Buffer_filter::Buffer_filter() { }

Buffer_filter::Buffer_filter(int buf_size, const std::initializer_list<std::string>& names) {
  for (const auto& name : names) {
    Bounded_buffer<Data>* buffer = new Bounded_buffer<Data>(buf_size);
    buffers[name] = std::unique_ptr<Bounded_buffer<Data>>(buffer);
  }
}

void Buffer_filter::push(const Data& d) {
  buffers[d.request_origin]->enqueue(d);
}

Data Buffer_filter::pop(const std::string& name) {
  return buffers[name]->dequeue();
}
