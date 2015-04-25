/* 
File: semaphore.h

Author: R. Bettati
Department of Computer Science
Texas A&M University
Date  : 08/02/11

*/

#ifndef _semaphore_H_                   // include file only once
#define _semaphore_H_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <mutex>
#include <pthread.h>
#include <condition_variable>
#include <atomic>

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CLASS   S e m a p h o r e  */
/*--------------------------------------------------------------------------*/

class Semaphore {
private:

  // resource count
  int value;
  //std::mutex mtx;
  //std::condition_variable_any cv;
  pthread_mutex_t mtx;
  pthread_cond_t cv;

public:

  /* -- CONSTRUCTOR/DESTRUCTOR */

  Semaphore(int _val);
  Semaphore(const Semaphore& other) = delete;
  Semaphore& operator=(const Semaphore& other) = delete;
  Semaphore() : Semaphore(1) { } // initializes to mutex

  ~Semaphore();

  /* -- SEMAPHORE OPERATIONS */

  // acquire a resource
  int P();

  // release a resource
  int V();

  // return number of resources available to "acquire"
  int resources_available() const { return value; }
};


#endif
