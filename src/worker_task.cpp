#include <string>
#include "worker_task.h"
#include "bounded_buffer.h"

Worker_task::Worker_task(Bounded_buffer<Data>& buf, RequestChannel& channel) : buffer(buf), channel(channel) { }

void Worker_task::run() {
    while (!cancelled) {
        Data d = buffer.dequeue();
        std::string request = d.request_origin;
        channel.send_request(request);
    }
}
