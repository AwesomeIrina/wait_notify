#include "barrier_synch.h"

void barrier_synch::wait(std::unique_lock<std::mutex> &lock)
{
    //std::unique_lock<std::mutex> lock(m_mu);
    cv.wait(lock, [&]{
        return !task_collection.empty();
    });

}

void someTask1()
{
   std::this_thread::sleep_for(std::chrono::milliseconds(500));
   std::cout<<"Task1"<<std::endl;
}

void someTask2()
{
   std::this_thread::sleep_for(std::chrono::seconds(1));
   std::cout<<"Task2"<<std::endl;
}

void barrier_synch::prepare_data()
{
    std::default_random_engine random_engine(rand()%10);
    std::uniform_int_distribution<int> int_distrib(10, 1000);
    int value = int_distrib(random_engine);

    std::unique_lock<std::mutex> lock(m_mu);
    if(value<500){
        std::function<void()> ptr =[](){someTask1();};
        task_collection.push(ptr);
        cv.notify_one();
    }
    else{
        std::function<void()> ptr =[](){someTask2();};
        task_collection.push(ptr);
        cv.notify_one();
    }

    lock.unlock();

    counter+=1;
    if(counter>=max_counter){
        return;
    }

    prepare_data();
}

void barrier_synch::extract_data()
{
    std::unique_lock<std::mutex> lock(m_mu);
    wait(lock);
//    cv.wait(lock,[this]{
//        return !task_collection.empty();
//    });

    (task_collection.back())();
    task_collection.pop();
    lock.unlock();
    if(counter>=max_counter){
        return;
    }

    extract_data();
}
