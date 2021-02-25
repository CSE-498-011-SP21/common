/****************************************************
 *
 * Logging Implementation
 *
 ****************************************************/

#ifndef KVCG_LOGGING_H
#define KVCG_LOGGING_H

#include <iostream>

/* Available log levels */
enum LogLevel { ERROR, WARNING, INFO,
                DEBUG, DEBUG2, DEBUG3, DEBUG4 };

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
 * No promises on thread safety...
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
    operator << ("["+getLabel(l)+"]:");
  }
  ~LOG() {
    if (opened) std::cerr << std::endl;
    opened = false;
  }

  template<class T>
  LOG &operator<<(const T &msg) {
    if (msgLevel <= LOG_LEVEL) {
        std::cerr << msg;
        opened = true;
    }
    return *this;
  }
private:
  bool opened;
  LogLevel msgLevel;

  inline std::string getLabel(LogLevel l) {
    switch(l) {
      case ERROR: return "ERROR";
      case WARNING: return "WARNING";
      case INFO: return "INFO";
      case DEBUG: return "DEBUG";
      case DEBUG2: return "DEBUG2";
      case DEBUG3: return "DEBUG3";
      case DEBUG4: return "DEBUG4";
    }
    return "-";
  }
};

#define LOG(X) LOG(X) << __func__ <<"(): "

#endif // KVCG_LOGGING_H
