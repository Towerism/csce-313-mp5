#include <cstring>
#include "network_req_channel.h"
NetworkRequestChannel::NetworkRequestChannel(const std::string _name, const Side _side, int _sockfd): my_name(_name), my_side(_side), my_sockfd(_sockfd){
  //if(_side == SERVER_SIDE){
  //
  //}
  //else if (_side == CLIENT_SIDE){
  //read
  //}
  //else
  //std::cout << "Incorrect specification of the side.." << std::endl;
}

NetworkRequestChannel::~NetworkRequestChannel(){
  close(my_sockfd);
}

const int MAX_MESSAGE = 255;
std::string NetworkRequestChannel::send_request(std::string _request){
  cwrite(_request);
  std::string s = cread();
  return s;
}

std::string NetworkRequestChannel::cread(){

  char buf[MAX_MESSAGE];

  if (read(my_sockfd, buf, MAX_MESSAGE) < 0) {
    perror(std::string("NetworkRequestChannel (" + my_name + "): Error reading from pipe!").c_str());
  }

  std::string s = buf;
  return s;
}

int NetworkRequestChannel::cwrite(std::string _msg) {
  if (_msg.length() >= MAX_MESSAGE) {
    std::cerr << "Message too long for Channel!\n";
    return -1;
  }

  const char * s = _msg.c_str();

  if (write(my_sockfd, s, strlen(s)+1) < 0) {
    perror(std::string("Request Channel (" + my_name + ") : Error writing to pipe!").c_str());
  }
}
