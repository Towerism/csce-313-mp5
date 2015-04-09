#include <gtest/gtest.h>
#include "semaphore.h"

TEST(SemaphoreTest, Mutex) {
    Semaphore sem(1);
    EXPECT_EQ(1, sem.resources_available());
    sem.P();
    EXPECT_EQ(0, sem.resources_available());
    sem.V();
    EXPECT_EQ(1, sem.resources_available());
}

TEST(SemaphoreTest, Counting) {
    Semaphore sem(20);
    EXPECT_EQ(20, sem.resources_available());
    for (int i = 0; i < 20; ++i) {
        sem.P();
    }
    EXPECT_EQ(0, sem.resources_available());
    for (int i = 0; i < 20; ++i) {
        sem.V();
    }
    EXPECT_EQ(20, sem.resources_available());
}
