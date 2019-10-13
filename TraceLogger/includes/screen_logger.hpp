#ifndef SCREEN_LOGGER_H
#define SCREEN_LOGGER_H

#include <threaded_logger.hpp>
#include <stdio.h>

template<typename Data>
class ScreenLogger : public ThreadedLogger<Data>
{
public:

    ScreenLogger()
    {
    }

    virtual ~ScreenLogger() {
    }

    virtual void run() {
        Data line;
        do {
            while(ThreadedLogger<Data>::getQueue().try_pop(line)) {
                printf("%s\n", line.formatLog().c_str());

                //emulate slow write
                //std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            //std::this_thread::sleep_for(std::chrono::milliseconds(5));
        } while (!ThreadedLogger<Data>::getQueue().empty() || !ThreadedLogger<Data>::shouldTerminate());
    }
};

#endif
