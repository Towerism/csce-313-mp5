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
  Worker_task(Bounded_buffer<Data>* buf, Buffer_filter& out_bufs, RequestChannel& ctrl);
  ~Worker_task() { }

  virtual void run() override;

  void cancel() { channel->send_request("quit"); delete channel; cancelled = true;}
private:
  Bounded_buffer<Data>* buffer;
  Buffer_filter& out_buffers;
  RequestChannel* channel;
  bool cancelled = false;
};

#endif // WORKER_TASK_H
