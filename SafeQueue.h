//
// Created by papraczy on 05/11/2019.
//

#ifndef SERVER_SAFEQUEUE_H
#define SERVER_SAFEQUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;
//template<class T>
// A threadsafe-queue.
class SafeQueue
{
public:
    SafeQueue(void);

    ~SafeQueue(void);

    // pop an element and return a copy. Block if queue empty.
    //T pop();
    int pop();

    //  push an element to the back of the queue.
    //void push(T& item);
    void push(int& item);
    bool empty();

private:
    //std::queue<T> queue_;
    std::queue<int> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};


#endif //SERVER_SAFEQUEUE_H
