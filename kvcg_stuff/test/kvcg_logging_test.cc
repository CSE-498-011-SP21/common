//
// Created by depaulsmiller on 3/11/21.
//

#include <kvcg_log2.hh>

int LOG_LEVEL = TRACE;

const int COMPILE_LOG_LEVEL = DEBUG2;

int main() {

    LOG(ERROR) << "Error";

    DO_LOG(ERROR) << "Error";
    DO_LOG(DEBUG) << "Debug";
    DO_LOG(TRACE) << "Trace";

    return 0;

}