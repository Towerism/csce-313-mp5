#include "client_socket.h"

namespace clisocks{
  int connect_to_server(std::string hostname, int port){
    int sockfd; //socket file descriptor
    sockfd = sockwrap::create_socket();
    struct sockaddr_in host_address = sockwrap::setup_host_socket("127.0.0.1");
    sockwrap::connect_to_socket(sockfd, host_address);
    return sockfd;
  }
}
