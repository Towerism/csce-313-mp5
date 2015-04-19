#ifndef WORKER_TASK_H
#define WORKER_TASK_H

#include <string>
#include "runnable.h"
#include "bounded_buffer.h"
#include "reqchannel.h"
#include "data.h"
#include "buffer_filter.h"

struct Worker_task : public Runnable {
  // inputs are request buffer and control request channel
  Worker_task(Bounded_buffer<Data>& buf, Buffer_filter& out_bufs, RequestChannel* channel);
  ~Worker_task() { }

  virtual void run() override;

  void cancel() { cancelled = true; }
private:
  Bounded_buffer<Data>& buffer;
  Buffer_filter& out_buffers;
  RequestChannel* channel;
  bool cancelled = false;
};

#endif // WORKER_TASK_H
