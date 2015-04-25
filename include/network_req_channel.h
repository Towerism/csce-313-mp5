#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class NetworkRequestChannel {
 public:
  typedef enum {SERVER_SIDE, CLIENT_SIDE} Side;
 private:
  int my_sockfd; //should be already connected
  std::string my_name;
  Side my_side;

 public:
  NetworkRequestChannel(const std::string _name, const Side _side, int _sockfd);
  ~NetworkRequestChannel();

  /* Send a string over the channel and wait for a reply. */
  std::string send_request(std::string _request);

  std::string cread();
  /* Blocking read of data from the channel. Returns a string of characters
     read from the channel. Returns NULL if read failed. */

  int cwrite(std::string _msg);
  /* Write the data to the channel. The function returns the number of characters written
     to the channel. */

  inline std::string get_name(){return my_name;}
  inline int get_sockfd(){return my_sockfd;}
};
