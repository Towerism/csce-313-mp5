#pragma once

#include <gtest/gtest.h>
#include <pthread.h>
#include <vector>
#include "test_bounded_task.h"
#include "test_bounded_task_2.h"
#include "test_bounded_task_3.h"

struct BoundedBufferThreadTest : public ::testing::Test {
protected:
  BoundedBufferThreadTest() : buffer(10), task(new Test_bounded_task) {
    task2 = new Test_bounded_task_2(buffer);
    task3 = new Test_bounded_task_3(buffer);
  }

  ~BoundedBufferThreadTest() {
    delete task;
  }

  Bounded_buffer<int> buffer;
  Test_bounded_task* task;
  Test_bounded_task_2* task2;
  Test_bounded_task_3* task3;
  std::vector<pthread_t> threads;
};
