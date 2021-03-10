#include <QCoreApplication>
#include "barrier_synch.h"

int main()
{
    //первая часть четвёртой лабы
//    std::thread threads[10];
//    barrier_synch barrier;
//    for(int i =0; i<10; i++){
//        threads[i] = std::thread([&](){
//            std::this_thread::sleep_for(std::chrono::seconds(1));
//            barrier.wait();
//        });
//    }

//    for(auto& thread : threads){
//        if(thread.joinable()){
//            thread.join();
//        }
//    }

    //попытка на автомат
    std::mutex mtx;
    barrier_synch task(mtx);

    std::thread th([&](){
        task.prepare_data();
    });
    std::thread th1([&](){
        task.extract_data();
    });

    if(th.joinable()){
        th.join();
    }

    if(th1.joinable()){
        th1.join();
    }



    system("pause");
    return 0;
}
