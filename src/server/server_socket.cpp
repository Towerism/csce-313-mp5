#include "server_socket.h"

namespace servsocks{
  int start_up_server() {
    int sockfd; //socket file descriptor
    sockfd = sockwrap::create_socket();
    sockwrap::set_socket_options(sockfd);

    struct sockaddr_in host_address = sockwrap::setup_host_socket("127.0.0.1");

    sockwrap::bind_to_socket(sockfd, host_address);
    sockwrap::listen_to_socket(sockfd);
    //sockwrap::accept_loop(sockfd);
    return sockfd;
  }
}
