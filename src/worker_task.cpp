#include <string>
#include <cstring>
#include <unistd.h>
#include "worker_task.h"
#include "bounded_buffer.h"
#include "util.h"

Worker_task::Worker_task(Bounded_buffer<Data>* buf, Buffer_filter& out_bufs, NetworkRequestChannel& ctrl) : buffer(buf), out_buffers(out_bufs) {
  std::cout << "" << std::endl;
  std::string chan_handle = ctrl.send_request("newthread");
  //std::cout << "chan_handle: " << chan_handle << std::endl;
  //int client_sockfd = connect_to_server(server_hostname, port);
  channel = new NetworkRequestChannel(chan_handle, NetworkRequestChannel::CLIENT_SIDE, ctrl.get_hostname(), ctrl.get_port());
}

void Worker_task::run() {
    while (!cancelled) {
        Data d = buffer->dequeue();
        std::string response = channel->send_request(d.data);
        // make sure the response is a number before putting it in out_buffers
        if (is_number(response)) {
          out_buffers.push(Data(d.request_origin, response));
        }
    }
}
