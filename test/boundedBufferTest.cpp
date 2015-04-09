#include <gtest/gtest.h>
#include "bounded_buffer.h"

TEST(BoundedBufferTest, Enqueue) {
    Bounded_buffer<int> buffer(20);
    buffer.enqueue(1);

    EXPECT_EQ(1, buffer.get_size());
    EXPECT_EQ(19, buffer.get_sem_full().resources_available());
    EXPECT_EQ(1, buffer.get_sem_empty().resources_available());
}

TEST(BoundedBufferTest, Dequeue) {
    Bounded_buffer<int> buffer(20);
    buffer.enqueue(1);
    ASSERT_EQ(1, buffer.get_size());

    int item = buffer.dequeue();

    EXPECT_EQ(1, item);
    EXPECT_EQ(0, buffer.get_size());
    EXPECT_EQ(20, buffer.get_sem_full().resources_available());
    EXPECT_EQ(0, buffer.get_sem_empty().resources_available());
}
