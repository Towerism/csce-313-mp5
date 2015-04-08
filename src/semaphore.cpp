#include "semaphore.h"

Semaphore::Semaphore(int _val) : value(_val) { }

Semaphore::~Semaphore() { }

int Semaphore::P() {
    mtx.lock();
    while(value == 0) {
        cv.wait(mtx);
    }
    --value;
    mtx.unlock();
    return 0;
}

int Semaphore::V() {
    mtx.lock();
    ++value;
    cv.notify_all();
    mtx.unlock();
    return 0;
}
