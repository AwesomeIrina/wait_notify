#ifndef BARRIER_SYNCH_H
#define BARRIER_SYNCH_H
#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <random>
#include <functional>

class barrier_synch
{
    //очередь с типом указатель на функцию - задачу
    //
    const int max_counter = 20;
    int counter;
    std::queue<std::function<void()>> task_collection;
    std::mutex &m_mu;
    std::condition_variable cv;


public:
    barrier_synch(std::mutex& mu): m_mu(mu){counter = 0;}
    void wait(std::unique_lock<std::mutex>& lock);
    void extract_data();
    void prepare_data();

};

#endif // BARRIER_SYNCH_H
