#ifndef WORKER_TASK_H
#define WORKER_TASK_H

#include <string>
#include "runnable.h"
#include "bounded_buffer.h"
#include "reqchannel.h"

struct Worker_task : public Runnable {
    // inputs are request buffer and control request channel
    Worker_task(Bounded_buffer<std::string>& buf, RequestChannel& ctrl);
    ~Worker_task() { delete channel; }

    virtual void run() override;
    void clean_up() { channel->send_request("quit"); }
private:
    Bounded_buffer<std::string>& buffer;
    RequestChannel* channel;
};

#endif // WORKER_TASK_H
