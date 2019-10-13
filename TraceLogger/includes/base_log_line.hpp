#ifndef BASE_LOG_LINE_H
#define BASE_LOG_LINE_H

#include <string>

class BaseLogLine
{
public:

    BaseLogLine() {

    };

    virtual ~BaseLogLine() {

    };

    virtual std::string formatLog() const = 0;
};

#endif
