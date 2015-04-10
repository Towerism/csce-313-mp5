#ifndef TEST_TASK_H
#define TEST_TASK_H

#include "semaphore.h"

struct Account {
    Account() : cash(100), cash_mutex(1) { }

    void withdraw(int amt) {
        cash_mutex.P();
        cash -= amt;
        cash_mutex.V();
    }

    void deposit(int amt) {
        cash_mutex.P();
        cash += amt;
        cash_mutex.V();
    }

    int get_cash() const { return cash; }

private:
    int cash;

    Semaphore cash_mutex;
};

struct Test_task : public Runnable {
public:
    int get_cash() { return account.get_cash(); }
protected:
    virtual void run() override {
        for (int i = 0; i < 100; ++i) {
            account.withdraw(10);
            account.deposit(10);
        }
    }
private:
    Account account;
};

#endif // TEST_TASK_H
