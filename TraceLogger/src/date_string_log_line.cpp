#include <sstream>
#include <ctime>
#include <iomanip>
#include "date_string_log_line.hpp"

DateStringLogLine::DateStringLogLine() {

};

DateStringLogLine::DateStringLogLine(std::string const & log) {
    now = std::chrono::system_clock::now();
    now_tt = std::chrono::system_clock::to_time_t(now);
    now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    line = log;
}

DateStringLogLine::DateStringLogLine(const char *log) :
    DateStringLogLine(std::string(log)) {
}

std::string DateStringLogLine::formatLog() const {

    std::tm bt = *std::localtime(&now_tt);

    std::ostringstream oss;
    oss << std::put_time(&bt, "%H:%M:%S");     // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << now_ms.count();
    return oss.str()  + " - " + line;
}
