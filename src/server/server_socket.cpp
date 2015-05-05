#include "server_socket.h"

namespace servsocks{
  int start_up_server(std::string hostname, int port, int queue_limit) {
    int sockfd; //socket file descriptor
    sockfd = sockwrap::create_socket();
    sockwrap::set_socket_options(sockfd);

    struct sockaddr_in host_address = sockwrap::setup_host_socket(hostname, port);

    sockwrap::bind_to_socket(sockfd, host_address);
    sockwrap::listen_to_socket(sockfd, queue_limit);
    return sockfd;
  }
}
