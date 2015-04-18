#include <string>
#include "worker_task.h"
#include "bounded_buffer.h"

Worker_task::Worker_task(Bounded_buffer<Data>& buf, Buffer_filter& out_bufs, RequestChannel& channel) : buffer(buf), out_buffers(out_bufs), channel(channel) { }

void Worker_task::run() {
    while (!cancelled) {
        Data d = buffer.dequeue();
        std::string response = channel.send_request(d.request_origin);
        out_buffers.push(Data(d.request_origin, response));
    }
}
