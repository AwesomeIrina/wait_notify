#include "barrier_synch.h"

barrier_synch::barrier_synch()
{
    threadsNum = 10;
    threadsCounter = 0;
}

void barrier_synch::func1()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void barrier_synch::wait()
{
    std::unique_lock<std::mutex> lock(mtx);
    threadsCounter +=1;
    cv.wait(lock, [&]{
        return threadsCounter == threadsNum;
    });
    cv.notify_all();
}
