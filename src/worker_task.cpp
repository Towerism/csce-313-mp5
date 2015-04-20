#include <string>
#include <unistd.h>
#include "worker_task.h"
#include "bounded_buffer.h"

Worker_task::Worker_task(Bounded_buffer<Data>* buf, Buffer_filter& out_bufs, RequestChannel& ctrl) : buffer(buf), out_buffers(out_bufs), channel(channel) {
  std::string chan_handle = ctrl.send_request("newthread");
  //std::cout << "chan_handle: " << chan_handle << std::endl;
  channel = new RequestChannel(chan_handle, RequestChannel::CLIENT_SIDE);
}

void Worker_task::run() {
    while (!cancelled) {
        Data d = buffer->dequeue();
        std::string response = channel->send_request(d.data);
        out_buffers.push(Data(d.request_origin, response));
    }
}
