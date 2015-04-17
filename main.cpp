/* 
    File: simpleclient.cpp

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2013/01/31

    Simple client main program for MP3 in CSCE 313
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
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <vector>

#include <errno.h>
#include <unistd.h>

#include "reqchannel.h"
#include "bounded_buffer.h"
#include "client_task.h"
#include "worker_task.h"
#include "runnable.h"

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
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {

  pid_t pid = fork();
  if (pid <= 0) {
      execv("data_server", argv);
  }

  int n = 10000;
  int b = 100;
  int w = 2;

  cout << "CLIENT STARTED:" << endl;

  cout << "Establishing control channel... " << flush;
  RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
  cout << "done." << endl;

  Bounded_buffer<string> buffer(b);

  /* create client threads */
  vector<pthread_t> client_threads;
  vector<Client_task> client_tasks;

  client_tasks.emplace_back("Joe Smith", buffer, n);
  client_tasks.emplace_back("Jane Smith", buffer, n);
  client_tasks.emplace_back("John Doe", buffer, n);

  for (auto& ct : client_tasks) {
      pthread_t t;
      pthread_create(&t, nullptr, Runnable::run_thread, &ct);
      client_threads.push_back(t);
  }

  /* create worker threads */
  vector<pthread_t> worker_threads;
  vector<Worker_task> worker_tasks;

  for (int i = 0; i < w; ++i) {
    worker_tasks.emplace_back(buffer, chan);
  }
  for (auto& wt : worker_tasks) {
    pthread_t t;
    pthread_create(&t, nullptr, Runnable::run_thread, &wt);
    worker_threads.push_back(t);
  }

  /* create histogram threads */


  /* wait for clients to finish and clean up */
  for (auto t : client_threads) {
    pthread_join(t, nullptr);
  }
  for (auto& wt : worker_tasks) {
    wt.clean_up();
  }

  string quit_reply = chan.send_request("quit");
  cout << "Reply to request 'quit' is '" << quit_reply << "'" << endl;
}
