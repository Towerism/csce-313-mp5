#include "semaphore.h"

Semaphore::Semaphore(int _val) : value(_val) { 
  pthread_mutex_init(&mtx, nullptr);
  pthread_cond_init(&cv, nullptr);
}

Semaphore::~Semaphore() {
  pthread_mutex_destroy(&mtx);
  pthread_cond_destroy(&cv);
}

int Semaphore::P() {
  pthread_mutex_lock(&mtx);
  while(value == 0) {
    pthread_cond_wait(&cv, &mtx);
  }
  --value;
  pthread_mutex_unlock(&mtx);
  return 0;
}

int Semaphore::V() {
  pthread_mutex_lock(&mtx);
  ++value;
  pthread_cond_signal(&cv);
  pthread_mutex_unlock(&mtx);
  return 0;
}
