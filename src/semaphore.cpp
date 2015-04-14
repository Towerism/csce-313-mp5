#include "semaphore.h"

Semaphore::Semaphore(int _val) : value(_val), wakeups(0) { }

Semaphore::~Semaphore() { }

int Semaphore::P() {
    mtx.lock();
    cv.wait(mtx, [this]() -> bool { return value > 0; });
    --value;
    mtx.unlock();
    return 0;
}

int Semaphore::V() {
    mtx.lock();
    ++value;
    cv.notify_one();
    mtx.unlock();
    return 0;
}
