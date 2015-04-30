/*
    File: dataserver.cpp

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2012/07/16

    Dataserver main program for MP3 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <cstring>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "network_req_channel.h"
#include "server_socket.h"

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* VARIABLES */
/*--------------------------------------------------------------------------*/

static int nthreads = 0;
int SERVER_SOCKFD;

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

void handle_process_loop(NetworkRequestChannel * _channel);

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- SUPPORT FUNCTIONS */
/*--------------------------------------------------------------------------*/

string int2string(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- THREAD FUNCTIONS */
/*--------------------------------------------------------------------------*/

void * handle_data_requests(void * args) {

  NetworkRequestChannel * data_channel =  (NetworkRequestChannel*)args;

  // -- Handle client requests on this channel.

  handle_process_loop(data_channel);

  // -- Client has quit. We remove channel.

  delete data_channel;
}

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- INDIVIDUAL REQUESTS */
/*--------------------------------------------------------------------------*/

void process_hello(NetworkRequestChannel & _channel, const string & _request, int sockfd) {
  std::cout << "recieved hello on socket: " << sockfd;
  _channel.cwrite("hello to you too");
}

void process_data(NetworkRequestChannel & _channel, const string &  _request, int sockfd) {
  usleep(1000 + (rand() % 5000));
  //_channel.cwrite("here comes data about " + _request.substr(4) + ": " + int2string(random() % 100));
  _channel.cwrite(int2string(rand() % 100), sockfd);
}

void process_newthread(NetworkRequestChannel & _channel, const string & _request, int sockfd) {
  int error;
  nthreads ++;

  // -- Name new data channel

  string new_channel_name = "data" + int2string(nthreads) + "_";
  //cout << "new channel name = " << new_channel_name << endl;

  // -- Pass new channel name back to client

  _channel.cwrite(new_channel_name, sockfd);

  // -- Construct new data channel (pointer to be passed to thread function)

  NetworkRequestChannel * data_channel = new NetworkRequestChannel(new_channel_name, NetworkRequestChannel::SERVER_SIDE, _channel.get_sockfd());

  // -- Create new thread to handle request channel

  pthread_t thread_id;
  //  cout << "starting new thread " << nthreads << endl;
  if (error = pthread_create(& thread_id, NULL, handle_data_requests, data_channel)) {
    fprintf(stderr, "p_create failed: %s\n", strerror(error));
  }

}

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- THE PROCESS REQUEST LOOP */
/*--------------------------------------------------------------------------*/

void process_request(NetworkRequestChannel & _channel, const string & _request, int sockfd) {

  if (_request.compare(0, 5, "hello") == 0) {
    process_hello(_channel, _request, sockfd);
  }
  else if (_request.compare(0, 4, "data") == 0) {
    process_data(_channel, _request, sockfd);
  }
  else if (_request.compare(0, 9, "newthread") == 0) {
    process_newthread(_channel, _request, sockfd);
  }
  else {
    _channel.cwrite("unknown request", sockfd);
  }

}

void *connection_handler(void *socket_desc);
void handle_process_loop(NetworkRequestChannel * _channel) {

  int client_sock, c;
  struct sockaddr_in client;
  //cout << "Reading next request from channel (" << _channel.name() << ") ..." << flush;
	pthread_t thread_id;
  //int new_sockfd = sockwrap::accept_connection(_channel->get_sockfd());
  while( (client_sock = accept(_channel->get_sockfd(), (struct sockaddr *)&client, (socklen_t*)&c)) ) {
    if(client_sock >= 0){
      NetworkRequestChannel * new_channel = new NetworkRequestChannel(_channel->get_name(), _channel->get_side(), client_sock);
      if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) new_channel) < 0)
        {
          perror("could not create thread");
        }
    }
  }

}
/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {

  SERVER_SOCKFD = servsocks::start_up_server();
  //  cout << "Establishing control channel... " << flush;
  NetworkRequestChannel *control_channel = new NetworkRequestChannel("control", NetworkRequestChannel::SERVER_SIDE, SERVER_SOCKFD);
  //  cout << "done.\n" << flush;

  handle_process_loop(control_channel);

}

//from stackoverflow
void *connection_handler(void * _channel)
{
  //Get the socket descriptor
  NetworkRequestChannel channel = *(NetworkRequestChannel *)_channel;
  int sock = channel.get_sockfd();
  int read_size;
  //char * client_message[2000];
  char *message , client_message[2000];

  //Receive a message from client
  while( (read_size = recv(sock, client_message , 2000 , 0)) > 0 )
    {

      //string request = channel->cread(new_sockfd);
      //cout << "New request is " << client_message << endl;
      if (client_message == "quit") {
        channel.cwrite("bye", sock);
        usleep(10000);          // give the other end a bit of time.
        break;                  // break out of the loop;
      }
      //char test_message[100] = "15\0";
      //if(send(sock, test_message, strlen(test_message), 0) <= 0){
      //cout << "send error" << std::endl;
      //break;
      //}
      process_request(channel, string(client_message), sock);
    }

  cout << "Closing connection_handler loop" << std::endl;
  if(read_size == 0)
    {
      puts("Client disconnected");
      fflush(stdout);
    }
  else if(read_size == -1)
    {
      perror("recv failed");
    }

  return 0;
}
