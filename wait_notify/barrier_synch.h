#ifndef BARRIER_SYNCH_H
#define BARRIER_SYNCH_H
#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>

class barrier_synch
{
private:
   bool ready;
   int threadsCounter;
   int threadsNum;
   std::condition_variable cv;
   std::mutex mtx;
public:
    barrier_synch();
    void wait();
    void notify();
};

#endif // BARRIER_SYNCH_H
