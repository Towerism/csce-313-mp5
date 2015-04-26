#include <server.hh>
#include <cstring>


namespace servsocks{
  int start_up_server() {
    int sockfd; //socket file descriptor
    sockfd = create_socket();
    set_socket_options(sockfd);

    struct sockaddr_in host_address = setup_host_socket();

    bind_to_socket(sockfd, host_address);
    listen_to_socket(sockfd);
    accept_loop(sockfd);
    return sockfd;
  }

  void set_socket_options(int host_sockfd){
    int on = 1;
    int off = 1;

    int status_of_set = setsockopt(host_sockfd, SOL_SOCKET, SO_DEBUG, &on, sizeof(on));
    //int status_of_set2 = setsockopt(host_sockfd, SOL_SOCKET, SO_ERROR, &on, sizeof(on));
    if(status_of_set == -1){
      std::cerr << "Setting options failed with errno " << errno << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }

  int create_socket(){
    std::cout << "Creating socket...\n" << std::endl;
    int host_sockfd = socket(PF_INET, SOCK_STREAM, PROTOCOL);
    if(host_sockfd == -1){
      std::cerr << "Failed to create socket." << std::endl;
      std::exit(EXIT_FAILURE);
    }
    return host_sockfd;
  }

  void bind_to_socket(int host_sockfd, struct sockaddr_in &sa_i){
    int status_of_bind = bind(host_sockfd, (struct sockaddr *)&sa_i, sizeof(sa_i));
    if(status_of_bind == -1){
      std::cerr << "Binding to socket failed with errno " << errno << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
  void accept_loop(int host_sockfd){
    struct sockaddr_in client_address;
    while(true){ //accept incoming
      int inc_sockfd;
      socklen_t sin_size_restriction = sizeof(sockaddr_in);
      inc_sockfd = accept(host_sockfd, (struct sockaddr *)&client_address, &sin_size_restriction);
      //handle_connection(inc_sockfd, &client_address);
      if(inc_sockfd != -1){
        std::cout << "Got a request from..." << inc_sockfd << std::endl;
      }
    }
  }
  struct sockaddr_in setup_host_socket(){
    /* --from <netinet/in.h
    struct sockaddr_in:   short   sin_family;
                          u_short sin_port;
                          struct  in_addr sin_addr;
                          char    sin_zero[8];
    */
    struct sockaddr_in host_address;
    host_address.sin_family = AF_INET;
    host_address.sin_port = htons(PORT);
    host_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    //since memset can be optimized away, we use memcpy to scrub the rest of the struct
    char zero_out[8] = {0};
    memcpy(&(host_address.sin_zero), &zero_out, 8);
    return host_address;
  }

  void listen_to_socket(int host_sockfd) {
    if(listen(host_sockfd, QUEUE_LIMIT)){
      std::cerr << "Failed to listen to socket socket with errno " << errno << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }

}
