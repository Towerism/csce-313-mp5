#include <string>
#include "worker_task.h"
#include "bounded_buffer.h"

Worker_task::Worker_task(Bounded_buffer<std::string>& buf, RequestChannel& ctrl) : buffer(buf) {
    std::string channel_handle = ctrl.send_request("newthread");
    channel = new RequestChannel(channel_handle, RequestChannel::CLIENT_SIDE);
}

void Worker_task::run() {
    while (true) {
        std::string request = buffer.dequeue();
        channel->send_request(request);
    }
}
