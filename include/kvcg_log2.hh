//
// Created by depaulsmiller on 3/11/21.
//

#include "kvcg_logging.h"

#ifndef COMMON_KVCG_LOG2_HH
#define COMMON_KVCG_LOG2_HH

/**
 * Set compile time log level to disable compilation of logs
 */
extern const int COMPILE_LOG_LEVEL;

template<LogLevel LEVEL>
class LOG2 {
public:

    template<LogLevel L = LEVEL, std::enable_if_t<(L <= COMPILE_LOG_LEVEL)> * = nullptr>
    LOG2() {
        opened = false;
        // TODO: Add timestamp here
        operator<<("[" + getLabel(LEVEL) + "]:");
    }

    template<LogLevel L = LEVEL, std::enable_if_t<(L > COMPILE_LOG_LEVEL)> * = nullptr>
    LOG2() {}

    ~LOG2() {
        deconstruct();
    }

    template<class T>
    LOG2<LEVEL> &operator<<(const T &m) {
        output(m);
        return *this;
    }

private:
    bool opened;
    std::stringstream msg;

    inline std::string getLabel(LogLevel l) {
        switch (l) {
            case ERROR:
                return "ERROR";
            case WARNING:
                return "WARNING";
            case INFO:
                return "INFO";
            case DEBUG:
                return "DEBUG";
            case DEBUG2:
                return "DEBUG2";
            case DEBUG3:
                return "DEBUG3";
            case DEBUG4:
                return "DEBUG4";
            case TRACE:
                return "TRACE";
        }
        return "-";
    }

    template<LogLevel L = LEVEL, std::enable_if_t<(L <= COMPILE_LOG_LEVEL)> * = nullptr>
    inline void deconstruct() {
        if (opened) {
            msg << std::endl;
            std::cerr << msg.str();
        }
        opened = false;
    }

    template<LogLevel L = LEVEL, std::enable_if_t<(L > COMPILE_LOG_LEVEL)> * = nullptr>
    inline void deconstruct() {}

    template<typename T, LogLevel L = LEVEL, std::enable_if_t<(L <= COMPILE_LOG_LEVEL)> * = nullptr>
    inline void output(const T &m) {
        if (LEVEL <= LOG_LEVEL) {
            msg << m;
            opened = true;
        }
    }

    template<typename T, LogLevel L = LEVEL, std::enable_if_t<(L > COMPILE_LOG_LEVEL)> * = nullptr>
    inline void output(const T &m) {
    }

};

#define DO_LOG(L) LOG2<L>() << __func__ <<"(): " << __FILE__ << ":" << __LINE__ << " "

#endif //COMMON_KVCG_LOG2_HH
