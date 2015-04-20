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

  void print_usage();

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
  int w = 10;
  bool x = true;
  int flags, opt, errflag = 0;

  while ((opt = getopt(argc, argv, "xn:b:w:")) != -1) {
    switch (opt) {
      case 'n':
        n = atoi(optarg);
        break;
      case 'b':
        b = atoi(optarg);
        break;
      case 'w':
        w = atoi(optarg);
        break;
      case 'x':
        x = false;
      case ':':
        if (optopt == '\0') { break; }
        fprintf(stderr, "Option -%c requires an operand\n", optopt);
        ++errflag;
        break;
      case '?':
        fprintf(stderr, "Unrecognised option: -%c\n", optopt);
        ++errflag;
        break;
    }
  }

  if (errflag) {
    print_usage();
    exit(1);
  }
  if (n <= 0 || b <= 0 || w <= 0) {
    fprintf(stderr, "Arguments must be positive\n");
  }

  /*
   * Do client-esque things
   */

  RequestChannel chan("control", RequestChannel::CLIENT_SIDE);

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

    if (x) {
      std::shared_ptr<HistoWorld> histo_world(new HistoWorld);
      for (auto ht : histo_tasks) {
        histo_world->addClient(ht.get());
      }
      ascii_engine::Engine engine(20);
      engine.set_world(histo_world);
      engine.game_loop();
    }

  /* wait for clients to finish and clean up */

  for (auto t : client_threads) {
    pthread_join(t, nullptr);
  }

  while (buffer->get_size() > 0);
  for (int i = 0; i < worker_tasks.size(); ++i) {
    worker_tasks[i]->cancel();
  }

  string quit_reply = chan.send_request("quit");
}

void print_usage() {
  cout << "usage: ./mp4 [-n <num requests>] [-b <buffer limit>] [-w <num workthreads>] [-x disables graphics]\n";
}
