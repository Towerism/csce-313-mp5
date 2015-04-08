#ifndef SEMAPHORETEST_H
#define SEMAPHORETEST_H

#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include "semaphore.h"
#include "runnable.h"
#include "test_task.h"

struct SemaphoreTest : public ::testing::Test {
protected:
    SemaphoreTest() : task(new Test_task) { }

    ~SemaphoreTest() {
        delete task;
    }

    Test_task* task;
    std::vector<std::thread> threads;
};

#endif // SEMAPHORETEST_H
