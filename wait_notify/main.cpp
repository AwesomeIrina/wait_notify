#include <QCoreApplication>
#include "barrier_synch.h"


int main()
{
    std::thread threads[10];
    barrier_synch barrier;
    for(int i =0; i<10; i++){
        threads[i] = std::thread([&](){
            barrier.func1();
            barrier.wait();
        });
    }

    for(auto& thread : threads){
        if(thread.joinable()){
            thread.join();
        }
    }
    system("pause");
    return 0;
}
