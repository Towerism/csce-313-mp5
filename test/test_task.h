#ifndef TEST_TASK_H
#define TEST_TASK_H

#include "semaphore.h"

struct Test_task : public Runnable {
public:
    Test_task() : cash(100), cashMutex(1) { }
    int get_cash() { return cash; }
protected:
    virtual void run() override {
        for (int i = 0; i < 100; ++i) {
            withdraw(10);
            deposit(10);
        }
    }
private:
    int cash;

    void withdraw(int amt) {
        cashMutex.P();
        cash -= amt;
        cashMutex.V();
    }

    void deposit(int amt) {
        cashMutex.P();
        cash += amt;
        cashMutex.V();
    }

    Semaphore cashMutex;
};

#endif // TEST_TASK_H
