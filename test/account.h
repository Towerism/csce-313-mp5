#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "semaphore.h"

struct Account {
  Account(int initial) : cash(initial), cash_mutex(1) { }
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

#endif // ACCOUNT_H
