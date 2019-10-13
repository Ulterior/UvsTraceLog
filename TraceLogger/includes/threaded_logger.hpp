#ifndef THREADED_LOGGER_H
#define THREADED_LOGGER_H

#include <thread>
#include <concurrent_queue.hpp>

template<typename Data>
class ThreadedLogger
{
private:
    std::thread logger_thread;
    concurrent_queue<Data> q;
    bool t_exit;
public:

    ThreadedLogger() : t_exit(false)
    {
        logger_thread = std::thread(&ThreadedLogger<Data>::run, this);
    }

    virtual ~ThreadedLogger() {
    }

    virtual void run() = 0;

    void waitUntilDone() {
        t_exit = true;
        logger_thread.join();
    }

    void log(Data const &line) {
        q.push(line);
    }

    concurrent_queue<Data> & getQueue() {
        return q;
    }

    bool shouldTerminate() {
        return t_exit;
    }

};

#endif
