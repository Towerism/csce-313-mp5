#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <iostream>
#include <queue>
#include "semaphore.h"

template <typename T>
struct Bounded_buffer {
    Bounded_buffer(int buf_limit) :
        size(0), limit(buf_limit), empty_slots(buf_limit), full_slots(0), queue_mutex(1) { }

    void enqueue(T item);
    T dequeue();

    // getters
    int get_size() const { return size; }
    int get_limit() const { return limit; }

    // getters used for testing
    const Semaphore& get_sem_empty() const { return empty_slots; }
    const Semaphore& get_sem_full() const { return full_slots; }

private:
    std::queue<T> queue;

    int size;
    int limit;

    Semaphore empty_slots;
    Semaphore full_slots;
    Semaphore queue_mutex;
};

template <typename T>
void Bounded_buffer<T>::enqueue(T item) {
    //std::cout << "My limit: " << limit << std::endl;
    //std::cout << "My size: " << size << std::endl;
    empty_slots.P();
    queue_mutex.P();

    queue.push(item);
    ++size;

    queue_mutex.V();
    full_slots.V();
}

template <typename T>
T Bounded_buffer<T>::dequeue() {
    //std::cout << "My limit: " << limit << std::endl;
    //std::cout << "My size: " << size << std::endl;
    T ret;
    full_slots.P();
    queue_mutex.P();

    ret = queue.front();
    queue.pop();
    --size;

    queue_mutex.V();
    empty_slots.V();
    return ret;
}

#endif // BOUNDED_BUFFER_H
