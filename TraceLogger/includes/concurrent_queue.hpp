#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename Data>
class concurrent_queue
{
private:
    std::queue<Data> the_queue;
    mutable std::mutex the_mutex;
    std::condition_variable cv;

public:

    void push(Data const& data)
    {
        std::unique_lock<std::mutex> guard(the_mutex);
        the_queue.push (data);
        guard.unlock();
        cv.notify_one();
    }

    bool empty() const
    {
        std::unique_lock<std::mutex> guard(the_mutex);
        return the_queue.empty();
    }
/*
    Data& front()
    {
        std::unique_lock<std::mutex> guard(the_mutex);
        return the_queue.front();
    }
 */
    Data const& front() const
    {
        std::unique_lock<std::mutex> guard(the_mutex);
        return the_queue.front();
    }

    void wait_for_data()
    {
        std::unique_lock<std::mutex> guard(the_mutex);
        while(the_queue.empty())
        {
            cv.wait(guard);
        }
    }

    void wait_and_pop(Data& popped_value)
    {
        std::unique_lock<std::mutex> guard(the_mutex);
        while(the_queue.empty())
        {
            cv.wait(guard);
        }

        popped_value=the_queue.front();
        the_queue.pop();
    }

    bool try_pop(Data& popped_value)
    {
        std::unique_lock<std::mutex> guard(the_mutex);
        if(the_queue.empty())
        {
            return false;
        }

        popped_value=the_queue.front();
        the_queue.pop();
        return true;
    }

    void pop()
    {
        std::unique_lock<std::mutex> guard(the_mutex);
        the_queue.pop();
    }

    void wake()
    {
        printf("trying to wake\n");
        std::unique_lock<std::mutex> guard(the_mutex);
        printf("trying to wake notify\n");
        cv.notify_one();
    }

};

#endif
