#ifndef RUNNABLE_H
#define RUNNABLE_H

struct Runnable {
    virtual ~Runnable() {}

    // args passed from pthread_create()
    static void* run_thread(void* args) {
        Runnable* obj = static_cast<Runnable*>(args); 
        obj->run();
        return args;
    }
protected:
    virtual void run() = 0; // pure virtual function
};

#endif // RUNNABLE_H
