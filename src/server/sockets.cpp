#include <cstring>
#include "sockets.h"
#include "histo_client.h"

namespace sockwrap{
  void set_socket_options(int sockfd){
    int on = 1;
    int off = 1;

    int status = setsockopt(sockfd, SOL_SOCKET, SO_DEBUG, &on, sizeof(on));
    if(status == -1){
      std::cerr << "Setting options failed with errno " << errno << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }

  int create_socket(){
    std::cout << "Creating socket...\n" << std::endl;
    int sockfd = socket(PF_INET, SOCK_STREAM, PROTOCOL);
    if(sockfd == -1){
      std::cerr << "Failed to create socket with errno " << errno << std::endl;
      std::exit(EXIT_FAILURE);
    }
    return sockfd;
  }

  void bind_to_socket(int sockfd, struct sockaddr_in &sa_i){
    int status = bind(sockfd, (struct sockaddr *)&sa_i, sizeof(sa_i));
    if(status == -1){
      std::cerr << "Binding to socket failed with errno " << errno << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
  int accept_connection(int sockfd){
    struct sockaddr_in client_address;
    //while(true){ //accept incoming
    int inc_sockfd;
    socklen_t sin_size_restriction = sizeof(sockaddr_in);
    inc_sockfd = accept(sockfd, (struct sockaddr *)&client_address, &sin_size_restriction);
    //handle_connection(inc_sockfd, &client_address);
    if(inc_sockfd != -1){
      std::cout << "Got a request from..." << inc_sockfd << std::endl;
      return inc_sockfd;
    }
    return -1;
  }

  void listen_to_socket(int sockfd) {
    int status = listen(sockfd, QUEUE_LIMIT);
    if(status == -1) {
      std::cerr << "Failed to listen to socket with errno " << errno << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }


  void connect_to_socket(int sockfd, struct sockaddr_in &sa_i){
    int status = connect(sockfd, (struct sockaddr *)&sa_i, sizeof(sa_i));
    if(status == -1){
      std::cerr << "Connecting to socket failed with errno " << errno << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }

  struct sockaddr_in setup_host_socket(std::string ip_address){
    /* --from <netinet/in.h
       struct sockaddr_in:   short   sin_family;
       u_short sin_port;
       struct  in_addr sin_addr;
       char    sin_zero[8];
    */
    struct sockaddr_in host_address;
    host_address.sin_family = AF_INET;
    if(getuid() == 0){
      host_address.sin_port = htons(PORT_SUPER);
    }
    else{
      host_address.sin_port = htons(PORT);
    }
    host_address.sin_addr.s_addr = inet_addr(ip_address.c_str());
    //since memset can be optimized away, we use memcpy to scrub the rest of the struct
    char zero_out[8] = {0};
    memcpy(&(host_address.sin_zero), &zero_out, 8);
    return host_address;
  }

}
