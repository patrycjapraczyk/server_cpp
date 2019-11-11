//
// Created by papraczy on 05/11/2019.
//

#include <iostream>
#include "SafeQueue.h"
//template <class T>

SafeQueue::SafeQueue(void)
{

}
//template <class T>
SafeQueue::~SafeQueue(void)
{

}

// Add an element to the queue.
//template <class T>
void SafeQueue::push(string& item)
{
    std::unique_lock<std::mutex> mlock(mutex_);
    this->queue_.push(item);

    mlock.unlock();     // unlock before notificiation to minimize mutex contention
    cond_.notify_one(); // notify one waiting thread
}

// Get the "front"-element.
// If the queue is empty, wait till a element is avaiable.
//template <class T>
string SafeQueue::pop(void)
{
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
        cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    return item;
}