#pragma once
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


namespace sockwrap{
  //wraps setsockopt()
  void set_socket_options(int socket_file_descriptor);
  //wraps socket() call
  int create_socket();
  //wraps bind() call
  void bind_to_socket(int socket_file_descriptor, struct sockaddr_in &host_address);
  //wraps listen()
  void listen_to_socket(int socket_file_descriptor, int q_limit);
  //wraps connect()
  void connect_to_socket(int socket_file_descriptor, struct sockaddr_in &sa_i);

  //returns -1 if no connection is made
  int accept_connection(int socket_file_descriptor);
  struct sockaddr_in setup_host_socket(std::string ip_address, int port);
}

//deprecated now since we specify these things...
//we can't do port 80 if we're not superuser
#define PORT_SUPER 80 //the servers port that client's will connect to
#define PORT 1024 //if we're not superuser
#define PROTOCOL 0 //from /etc/protocols..this is the IP number
#define QUEUE_LIMIT 128 //note that backlog (aka socket queue) is limited to 128
