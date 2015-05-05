#pragma once
#include "sockets.h"

namespace clisocks{
  //creates a socket, connects to the specified server, and returns a socket file descriptor for a client socket
  int connect_to_server(std::string hostname, int port);
}
