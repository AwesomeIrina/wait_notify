#include <QCoreApplication>
#include "barrier_synch.h"


int main()
{
    std::thread threads[10];
    barrier_synch barrier;
    for(int i =0; i<10; i++){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        threads[i] = std::thread([&](){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout<<"thread i is wait i: "<<i<<std::endl;
            barrier.wait();
        });
    }
    barrier.notify();

    for(auto& thread : threads){
        if(thread.joinable()){
            thread.join();
        }
    }
    system("pause");
    return 0;
}

// condition_variable example
//#include <iostream>           // std::cout
//#include <thread>             // std::thread
//#include <mutex>              // std::mutex, std::unique_lock
//#include <condition_variable> // std::condition_variable

//std::mutex mtx;
//std::condition_variable cv;
//bool ready = false;
//int counter;
//void print_id (int id) {
//  std::unique_lock<std::mutex> lck(mtx);
//  std::cout<<"Here in print_id: "<<id<<std::endl;
//  while (!ready) {
//      counter = counter + 1;
//      std::cout<<"Here in print_id in while: "<<id<<std::endl;
//      cv.wait(lck);

//      std::cout<<"COUNTER in print_id in while: "<<counter<<std::endl;
//  };
//  std::cout<<"Here in print_id after while: "<<id<<std::endl;
//  // ...
//  std::cout << "thread " << id << '\n';
//}

//void go() {
//  std::unique_lock<std::mutex> lck(mtx);
//  ready = true;
//  cv.notify_all();
//}

//int main ()
//{
//  std::thread threads[10];
//  // spawn 10 threads:
//  for (int i=0; i<10; ++i)
//    threads[i] = std::thread(print_id,i);

//  std::cout<<"Here in main after for"<<std::endl;
//  std::cout << "10 threads ready to race...\n";
//  go();                       // go!

//  for (auto& th : threads) th.join();
//  system("pause");
//  return 0;
//}
