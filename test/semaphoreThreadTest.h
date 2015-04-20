#ifndef SEMAPHORETHREADTEST_H
#define SEMAPHORETHREADTEST_H

#include <gtest/gtest.h>
#include <thread>
#include <pthread.h>
#include <vector>
#include "semaphore.h"
#include "runnable.h"
#include "test_task.h"
#include "test_task_2.h"
#include "test_task_3.h"

struct SemaphoreThreadTest : public ::testing::Test {
protected:
  SemaphoreThreadTest() : task(new Test_task), task2(new Test_task_2), task3(new Test_task_3) { }

  ~SemaphoreThreadTest() {
    delete task;
  }

  Test_task* task;
  Test_task_2* task2;
  Test_task_3* task3;
  std::vector<pthread_t> threads;
};

#endif // SEMAPHORETHREADTEST_H
