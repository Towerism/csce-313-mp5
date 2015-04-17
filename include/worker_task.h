#ifndef WORKER_TASK_H
#define WORKER_TASK_H

#include <string>
#include "runnable.h"
#include "bounded_buffer.h"
#include "reqchannel.h"

struct Worker_task : public Runnable {
  // inputs are request buffer and control request channel
  Worker_task(Bounded_buffer<std::string>& buf, RequestChannel& channel);
  ~Worker_task() { }

  virtual void run() override;

  void cancel() { cancelled = true; }
private:
  Bounded_buffer<std::string>& buffer;
  RequestChannel& channel;
  bool cancelled = false;
};

#endif // WORKER_TASK_H
