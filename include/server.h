#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 80 //the servers port that client's will connect to
#define PROTOCOL 0 //from /etc/protocols..this is the IP number
#define QUEUE_LIMIT 128 //note that backlog (aka socket queue) is limited to 128

void start_up_server();
void exit_handler() {
  std::cout << "Exited successfully!" << std::endl;
}

//wraps socket() call
int create_socket();

//wraps setsockopt()
void set_socket_options(int socket_file_descriptor);

//wraps bind() call
void bind_to_socket(int socket_file_descriptor);

void accept_loop(int socket_file_descriptor);

