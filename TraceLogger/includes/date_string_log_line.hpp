#ifndef DATE_STRING_LOG_LINE_H
#define DATE_STRING_LOG_LINE_H

#include <base_log_line.hpp>
#include <string>
#include <chrono>

class DateStringLogLine : public BaseLogLine
{
protected:
    std::chrono::system_clock::time_point now;
    std::time_t now_tt;
    std::chrono::milliseconds now_ms;
    std::string line;

public:

    DateStringLogLine();

    DateStringLogLine(std::string const & log);
    DateStringLogLine(const char *log);

    virtual std::string formatLog() const;
};

#endif
