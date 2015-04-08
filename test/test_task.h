#ifndef TEST_TASK_H
#define TEST_TASK_H

#include <pthread.h>
#include "semaphore.h"

struct Test_task : public Runnable {
public:
    Test_task() : cash(100), cashMutex(1) { }
    int get_cash() { return cash; }
protected:
    virtual void run() override {
        // try to force a race condition
        for (int i = 0; i < 1000000; ++i) {
            withdraw(10);
            deposit(10);
        }
        pthread_exit(nullptr);
    }
private:
    int cash;

    void withdraw(int amt) {
        //cashMutex.P();
        cash -= 100;
        //cashMutex.V();
    }

    void deposit(int amt) {
        //cashMutex.P();
        cash += 100;
        //cashMutex.V();
    }

    Semaphore cashMutex;
};

#endif // TEST_TASK_H
