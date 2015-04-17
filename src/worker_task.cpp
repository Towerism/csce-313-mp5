#include <string>
#include "worker_task.h"
#include "bounded_buffer.h"

Worker_task::Worker_task(Bounded_buffer<std::string>& buf, RequestChannel& channel) : buffer(buf), channel(channel) { }

void Worker_task::run() {
    while (!cancelled) {
        std::string request = buffer.dequeue();
        channel.send_request(request);
    }
}
