#include <gtest/gtest.h>
#include "semaphoreTest.h"

TEST_F(SemaphoreTest, SingleThread) {
    threads.push_back(0);
    pthread_create(&threads[0], &attr, Runnable::run_thread, task);
    pthread_join(threads[0], nullptr);
    ASSERT_EQ(100, task->get_cash());
}

TEST_F(SemaphoreTest, MultiThread) {
    threads.push_back(0);
    threads.push_back(0);

    pthread_create(&threads[0], &attr, Runnable::run_thread, task);
    pthread_create(&threads[1], &attr, Runnable::run_thread, task);
    for (auto t : threads) {
        pthread_join(t, nullptr);
    }
    ASSERT_EQ(100, task->get_cash());

}
