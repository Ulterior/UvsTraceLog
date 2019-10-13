#include <stdio.h>
#include <date_string_log_line.hpp>
#include <screen_logger.hpp>

int main()
{
    ScreenLogger<DateStringLogLine> trace_logger;

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
