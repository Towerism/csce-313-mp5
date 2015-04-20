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
#include <memory>

#include <errno.h>
#include <unistd.h>

#include "reqchannel.h"
#include "bounded_buffer.h"
#include "client_task.h"
#include "worker_task.h"
#include "runnable.h"
#include "data.h"
#include "buffer_filter.h"
#include "histo_client.h"
#include "histo_world.h"
#include "ascii-engine/world.h"
#include "ascii-engine/engine.h"

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

  int n = 100;
  int b = 100;
  int w = 10;

  //cout << "CLIENT STARTED:" << endl;

  //cout << "Establishing control channel... " << flush;
  RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
  //cout << "done." << endl;

  std::shared_ptr<Bounded_buffer<Data>> buffer(new Bounded_buffer<Data>(b));

  /* create client threads */
  vector<pthread_t> client_threads;
  vector<shared_ptr<Client_task>> client_tasks;

  client_tasks.emplace_back(new Client_task("Joe Smith", buffer.get(), n));
  client_tasks.emplace_back(new Client_task("Jane Smith", buffer.get(), n));
  client_tasks.emplace_back(new Client_task("John Doe", buffer.get(), n));

  for (auto ct : client_tasks) {
      pthread_t t;
      pthread_create(&t, nullptr, Runnable::run_thread, ct.get());
      client_threads.push_back(t);
  }

  /* create worker threads */
  Buffer_filter out_buffers(b, {"Joe Smith", "Jane Smith", "John Doe"}); // conglomerated data server responses
  vector<pthread_t> worker_threads;
  vector<shared_ptr<Worker_task>> worker_tasks;

  for (int i = 0; i < w; ++i) {
    worker_tasks.emplace_back(new Worker_task(buffer.get(), out_buffers, chan));
  }
  for (auto wt : worker_tasks) {
    pthread_t t;
    pthread_create(&t, nullptr, Runnable::run_thread, wt.get());
    worker_threads.push_back(t);
  }

  /* create histogram threads */

  vector<pthread_t> histo_threads;
  vector<std::shared_ptr<HistoClient>> histo_tasks;

  histo_tasks.emplace_back(new HistoClient("Joe Smith", *out_buffers.get("Joe Smith")));
  histo_tasks.emplace_back(new HistoClient("Jane Smith", *out_buffers.get("Jane Smith")));
  histo_tasks.emplace_back(new HistoClient("John Doe", *out_buffers.get("John Doe")));

  for (auto ht : histo_tasks) {
    pthread_t t;
    pthread_create(&t, nullptr, Runnable::run_thread, ht.get());
    histo_threads.push_back(t);
  }

  ascii_engine::Engine engine(20);
  std::shared_ptr<HistoWorld> histo_world(new HistoWorld);
  for (auto ht : histo_tasks) {
    histo_world->addClient(ht.get());
  }
  engine.set_world(histo_world);
  engine.game_loop();


  /* wait for clients to finish and clean up */

  for (auto t : client_threads) {
    //std::cout << "waiting on client\n";
    pthread_join(t, nullptr);
  }
  //std::cout << "clients finished\n";

  while (buffer->get_size() > 0) {
    //std::cout << "buffer size: " << buffer->get_size() << std::endl;
  }
  for (int i = 0; i < worker_tasks.size(); ++i) {
    worker_tasks[i]->cancel();
  }

  string quit_reply = chan.send_request("quit");
  //cout << "Reply to request 'quit' is '" << quit_reply << "'" << endl;
}
