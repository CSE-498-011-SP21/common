/****************************************************
 *
 * Logging Implementation
 *
 ****************************************************/

#ifndef KVCG_LOGGING_H
#define KVCG_LOGGING_H

#include <iostream>
#include <sstream>

/* Available log levels */
enum LogLevel {
    ERROR = 0,
    WARNING = 1,
    INFO = 2,
    DEBUG = 3,
    DEBUG2 = 4,
    DEBUG3 = 5,
    DEBUG4 = 6,
    TRACE = 7
};

/* Define current loging level */
extern int LOG_LEVEL;

/**
 *
 * LOGGING CLASS
 *
 * Meant to be used in place of cout/cerr.
 * To use, set LOG_LEVEL to desired level.
 * It can be changed at runtime as well.
 * a message will only be displayed if
 * LOG_LEVEL is set above it.
 * To invoke, use just as cout/cerr -
 *
 * LOG(INFO) << "x is " << x;
 *
 * Note: No endl needed, added automatically.
 *
 * TBD: Log to file as well?
 * TBD: Ever use stdout? Use stderr for unbuffered
 *
 */
class LOG {
public:
    LOG() {}

    LOG(LogLevel l) {
        msgLevel = l;
        opened = false;
        // TODO: Add timestamp here
        operator<<("[" + getLabel(l) + "]:");
    }

    ~LOG() {
        if (opened) {
            msg << std::endl;
            std::cerr << msg.str();
        }
        opened = false;
    }

    template<class T>
    LOG &operator<<(const T &m) {
        if (msgLevel <= LOG_LEVEL) {
            msg << m;
            opened = true;
        }
        return *this;
    }

private:
    bool opened;
    LogLevel msgLevel;
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
};

#define LOG(X) LOG(X) << __func__ <<"(): "

template<LogLevel LEVEL>
class LOG2 {
public:

    LOG2() {
        opened = false;
        // TODO: Add timestamp here
        operator<<("[" + getLabel(LEVEL) + "]:");
    }

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

    inline void deconstruct() {
        if (opened) {
            msg << std::endl;
            std::cerr << msg.str();
        }
        opened = false;
    }

    template<typename T>
    inline void output(const T &m) {
        if (LEVEL <= LOG_LEVEL) {
            msg << m;
            opened = true;
        }
    }

};


#endif // KVCG_LOGGING_H
