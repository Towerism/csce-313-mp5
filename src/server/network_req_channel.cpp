#include <cstring>
#include "network_req_channel.h"
NetworkRequestChannel::NetworkRequestChannel(const std::string _name, const Side _side, int _sockfd): my_name(_name), my_side(_side), my_sockfd(_sockfd){}
NetworkRequestChannel::NetworkRequestChannel(const std::string _name, const Side _side, std::string _hostname, int _port): my_name(_name), my_side(_side), hostname(_hostname), port(_port){
  if (_side == CLIENT_SIDE){
    std::cout << "Client connecting to server..." << std::endl;
    my_sockfd = clisocks::connect_to_server(_hostname, _port);
    send_request("hello");
    if(my_sockfd < 0 ){
      std::cout << "fatal in networkreq constructor" << std::endl;
      std::exit(0);
    }
  }
}

NetworkRequestChannel::~NetworkRequestChannel(){
  close(my_sockfd);
}

std::string NetworkRequestChannel::send_request(std::string _request){
  cwrite(_request);
  std::string s = cread();
  return s;
}

std::string NetworkRequestChannel::cread(){
  return cread(my_sockfd);
}

const int MAX_MESSAGE = 2000;
std::string NetworkRequestChannel::cread(int sockfd){
  char buf[MAX_MESSAGE];

  if (recv(sockfd, buf, MAX_MESSAGE, 0) <= 0) {
    perror(std::string("NetworkRequestChannel (" + my_name + "): Error reading from socket!\n").c_str());
    return "Failure...";
  }
  std::string s = std::string(buf);
  return s;
}

int NetworkRequestChannel::cwrite(std::string _msg) {
  cwrite(_msg, my_sockfd);
}
int NetworkRequestChannel::cwrite(std::string _msg, int sockfd) {
  if (_msg.length() >= MAX_MESSAGE) {
    std::cerr << "Message too long for Channel!\n";
    return -1;
  }

  const char *s  = (_msg.c_str() + '\0');

  if (send(sockfd, s, MAX_MESSAGE, 0) < 0) {
    perror(std::string("Request Channel (" + my_name + ") : Error writing to pipe!\n").c_str());
  }
}
