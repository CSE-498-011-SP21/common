//
// Created by depaulsmiller on 3/11/21.
//

#include <type_traits>
#include <iostream>
#include <sstream>

#ifndef COMMON_KVCG_LOG2_HH
#define COMMON_KVCG_LOG2_HH

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
 * Set compile time log level to disable compilation of logs
 */
#ifdef COMPILE_LOG
inline const int COMPILE_LOG_LEVEL = COMPILE_LOG;
#else
inline const int COMPILE_LOG_LEVEL = TRACE;
#endif

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

// Cool constexpr from https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
template <typename T, size_t S>
inline constexpr size_t get_file_name_offset(const T (& str)[S], size_t i = S - 1) {
    return (str[i] == '/' || str[i] == '\\') ? i + 1 : (i > 0 ? get_file_name_offset(str, i - 1) : 0);
}

template <typename T>
inline constexpr size_t get_file_name_offset(T (& str)[1]) {
    return 0;
}

#define __FILENAME__ &__FILE__[get_file_name_offset(__FILE__)]

#define LOG(L) LOG2<L>() << __func__ <<"(): "
#define DO_LOG(L) LOG2<L>() << __func__ <<"(): " << __FILENAME__ << ":" << __LINE__ << " "

#endif //COMMON_KVCG_LOG2_HH
