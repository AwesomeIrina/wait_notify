#include "barrier_synch.h"

barrier_synch::barrier_synch()
{
    ready = false;
    threadsCounter = 0;
    threadsNum = 10;
}

void barrier_synch::wait()
{
    std::unique_lock<std::mutex> lock(mtx);
    threadsCounter +=1;
    std::cout<<"counter"<<threadsCounter<<std::endl;
    while(!ready){
        cv.wait(lock);
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<<"counter after chrono"<<threadsCounter<<std::endl;
}

void barrier_synch::notify()
{
    std::unique_lock<std::mutex> lock(mtx);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<<"counter after"<<threadsCounter<<std::endl;
    //std::cout<<"counter"<<threadsCounter<<std::endl;
    ready = true;
    cv.notify_all();
}
