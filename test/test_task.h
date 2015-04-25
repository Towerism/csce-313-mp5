#ifndef TEST_TASK_H
#define TEST_TASK_H

#include "semaphore.h"
#include "account.h"

struct Test_task : public Runnable {
public:
  Test_task() : account(100) { }
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
