#pragma once

#include "bounded_buffer.h"
#include "runnable.h"

struct Test_bounded_task_2 : public Runnable {
public:
  Test_bounded_task_2(Bounded_buffer<int>& b) : buffer(b) { }
  int get_buffer_size() const { return buffer.get_size(); }
protected:
  virtual void run() override {
    for (int i = 0; i < 1000; ++i) {
      buffer.dequeue();
    }
  }
  Bounded_buffer<int>& buffer;
};
