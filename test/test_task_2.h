#ifndef TEST_TASK_2_H
#define TEST_TASK_2_H

#include "semaphore.h"
#include "account.h"

struct Test_task_2 : public Runnable {
public:
  Test_task_2() : account(100) { }
  int get_cash() { return account.get_cash(); }
protected:
  virtual void run() override {
    for (int i = 0; i < 100; ++i) {
      account.deposit(10);
    }
  }
private:
  Account account;
};

#endif // TEST_TASK_2_H
