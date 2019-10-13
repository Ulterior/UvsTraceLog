#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include <threaded_logger.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

template<typename Data>
class FileLogger : public ThreadedLogger<Data>
{
private:

    std::ofstream logfile;
public:

    FileLogger(std::string const & outputFileName)
    {
        logfile.open(outputFileName, std::ios::out | std::ios::app);
        if (!logfile.is_open()) {
            throw std::invalid_argument( "Unable to open logfile" );
        }
    }

    virtual ~FileLogger() {
        if (logfile.is_open()) {
            logfile.close();
        }
    }

    virtual void run() {

        Data line;
        do {
            while(ThreadedLogger<Data>::getQueue().try_pop(line)) {
                logfile << line.formatLog() << std::endl;
                logfile.flush();

                //emulate slow write
                //std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            //std::this_thread::sleep_for(std::chrono::milliseconds(5));
        } while (!ThreadedLogger<Data>::getQueue().empty() || !ThreadedLogger<Data>::shouldTerminate());
    }

};

#endif
