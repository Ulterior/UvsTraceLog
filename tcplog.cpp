#include <iostream>
#include <stdio.h>
#include <date_string_log_line.hpp>
#include <tcp_logger.hpp>

int main(int argc, char* argv[])
{
    // Check the number of parameters
    if (argc < 2) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " port number" << std::endl;
        return 1;
    }

    TcpLogger<DateStringLogLine> trace_logger("127.0.0.1", atoi(argv[1]));

    printf("Started populating\n");
    char ll[256];
    int MAX = 500;
    for(int i=0; i<MAX; i++) {
        sprintf(ll, "line %d/%d", i, MAX);
        trace_logger.log(DateStringLogLine(ll));
        //emulate app latency
        //std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50));
    }

    printf("Application is done, waiting for trace logger\n");

    trace_logger.waitUntilDone();

    return 0;
}
