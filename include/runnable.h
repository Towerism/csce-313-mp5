#ifndef RUNNABLE_H
#define RUNNABLE_H

struct Runnable {
  virtual ~Runnable() {}

  static void* run_thread(void* obj) {
    Runnable* runnable = static_cast<Runnable*>(obj);
    runnable->run();
  }
  protected:
  virtual void run() = 0; // pure virtual function
};

#endif // RUNNABLE_H
