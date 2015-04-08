#ifndef SEMAPHORETEST_H
#define SEMAPHORETEST_H

#include <gtest/gtest.h>
#include <pthread.h>
#include <vector>
#include "semaphore.h"
#include "runnable.h"
#include "test_task.h"

struct SemaphoreTest : public ::testing::Test {
protected:
    SemaphoreTest() : task(new Test_task) {
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    }

    ~SemaphoreTest() {
        delete task;
        pthread_attr_destroy(&attr);
    }

    Test_task* task;
    std::vector<pthread_t> threads;
    pthread_attr_t attr;
};

#endif // SEMAPHORETEST_H
