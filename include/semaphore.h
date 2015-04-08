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
#include <condition_variable>

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
    /* -- INTERNAL DATA STRUCTURES
        You may need to change them to fit your implementation. */

    // resource count
    int value;
    std::mutex mtx;
    std::condition_variable_any cv;

    bool is_value_zero() { return value == 0; }

public:

    /* -- CONSTRUCTOR/DESTRUCTOR */

    Semaphore(int _val);

    ~Semaphore();

    /* -- SEMAPHORE OPERATIONS */

    // acquire a resource
    int P();

    // release a resource
    int V();
};


#endif
