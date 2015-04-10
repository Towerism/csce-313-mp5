#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <queue>
#include <vector>
#include "semaphore.h"

template <typename T>
struct Bounded_buffer {
    Bounded_buffer(int buf_limit) : 
        size(0), limit(buf_limit), empty_queue(0), full_queue(buf_limit), queue_mutex(1) { }

    void enqueue(T item);
    T dequeue();

    // getters
    int get_size() const { return size; }
    int get_limit() const { return limit; }

    // getters used for testing
    const Semaphore& get_sem_empty() const { return empty_queue; }
    const Semaphore& get_sem_full() const { return full_queue; }

private:
    std::queue<T> queue;

    int size;
    int limit;
    Semaphore empty_queue;
    Semaphore full_queue;
    Semaphore queue_mutex;
};

template <typename T>
void Bounded_buffer<T>::enqueue(T item) {
    full_queue.P();
    queue_mutex.P();

    queue.push(item);
    ++size;

    queue_mutex.V();
    empty_queue.V();
}

template <typename T>
T Bounded_buffer<T>::dequeue() {
    T ret;
    empty_queue.P();
    queue_mutex.P();

    ret = queue.front();
    queue.pop();
    --size;

    queue_mutex.V();
    full_queue.V();
    return ret;
}

#endif // BOUNDED_BUFFER_H
