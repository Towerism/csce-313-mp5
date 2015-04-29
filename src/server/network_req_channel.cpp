#include "network_req_channel.h"
NetworkRequestChannel::NetworkRequestChannel(const std::string _name, const Side _side, int _sockfd): my_name(_name), my_side(_side), my_sockfd(_sockfd){}
NetworkRequestChannel::NetworkRequestChannel(const std::string _name, const Side _side, std::string _hostname, int _port): my_name(_name), my_side(_side), hostname(_hostname), port(_port){
  //if(_side == SERVER_SIDE){
  //
  //}
  if (_side == CLIENT_SIDE){
    //std::cout << "Connecting to server..." << std::endl;
    my_sockfd = clisocks::connect_to_server(_hostname, _port);
    if(my_sockfd < 0 )
      std::exit(0);
  }
  //else
}

NetworkRequestChannel::~NetworkRequestChannel(){
  close(my_sockfd);
}

std::string NetworkRequestChannel::send_request(std::string _request){
  cwrite(_request);
  std::string s = cread();
  //std::cout << "send_request returned " << s << std::endl;
  //s = " ";
  return s;
}

std::string NetworkRequestChannel::cread(){
  cread(my_sockfd);
}

const int MAX_MESSAGE = 2000;
std::string NetworkRequestChannel::cread(int sockfd){
  char buf[MAX_MESSAGE];

  if (recv(sockfd, buf, MAX_MESSAGE, MSG_TRUNC) < 0) {
    perror(std::string("NetworkRequestChannel (" + my_name + "): Error reading from pipe!\n").c_str());
    //std::cout << "My sock_fd is: " << my_sockfd << " and errno: " << errno << std::endl;
  }
  //std::cout << "MY MESSAGE IS::::::: " << buf << std::endl;
  std::string s(buf);
  //std::cout << "Message still IS:::::" << buf << std::endl;
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

  const char *s  = _msg.c_str();

  if (send(sockfd, s, MAX_MESSAGE, 0) < 0) {
    perror(std::string("Request Channel (" + my_name + ") : Error writing to pipe!\n").c_str());
  }
}
