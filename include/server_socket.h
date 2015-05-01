#pragma once
#include "sockets.h"

namespace servsocks{
  int start_up_server(std::string hostname, int port, int queue_limit);
}
