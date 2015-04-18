#include "boundedBufferThreadTest.h"

TEST_F(BoundedBufferThreadTest, SingleThread) {
  pthread_t t;
  pthread_create(&t, nullptr, Runnable::run_thread, task);
  threads.push_back(t);
  for (auto t : threads) {
    pthread_join(t, nullptr);
  }
  ASSERT_EQ(0, task->get_buffer_size());
}

TEST_F(BoundedBufferThreadTest, MultiThread) {
  for (int i = 0; i < 32; ++i) {
    pthread_t t;
    pthread_create(&t, nullptr, Runnable::run_thread, task);
    threads.push_back(t);
  }
  for (auto t : threads) {
    pthread_join(t, nullptr);
  }
  ASSERT_EQ(0, task->get_buffer_size());
}
