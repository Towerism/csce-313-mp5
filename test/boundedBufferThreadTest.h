#pragma once

#include <gtest/gtest.h>
#include <pthread.h>
#include <vector>
#include "test_bounded_task.h"

struct BoundedBufferThreadTest : public ::testing::Test {
protected:
  BoundedBufferThreadTest() : task(new Test_bounded_task) { }

  ~BoundedBufferThreadTest() {
    delete task;
  }

  Test_bounded_task* task;
  std::vector<pthread_t> threads;
};
