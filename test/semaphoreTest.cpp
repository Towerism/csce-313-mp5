#include <gtest/gtest.h>
#include <thread>
#include "semaphoreTest.h"

TEST_F(SemaphoreTest, SingleThread) {
    threads.push_back(std::thread(Runnable::run_thread, task));
    threads[0].join();
    
    ASSERT_EQ(100, task->get_cash());
}

TEST_F(SemaphoreTest, MultiThread) {
    for (int i = 0; i < 3; ++i) {
        threads.push_back(std::thread(Runnable::run_thread, task));
    }
    for (auto& t : threads) {
        t.join();
    }
    ASSERT_EQ(100, task->get_cash());

}
