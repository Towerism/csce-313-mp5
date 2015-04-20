#ifndef CLIENT_TASK_H
#define CLIENT_TASK_H

#include <string>
#include "runnable.h"
#include "bounded_buffer.h"
#include "data.h"

struct Client_task : public Runnable {
    Client_task(const std::string& name, Bounded_buffer<Data>* buf, int requests=10000) : 
        name(name), buffer(buf), requests_to_send(requests) { }

    virtual void run() override;
private:
    std::string name;
    Bounded_buffer<Data>* buffer;
    int requests_to_send;
};

#endif // CLIENT_TASK_H
