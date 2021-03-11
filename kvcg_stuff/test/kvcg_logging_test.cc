//
// Created by depaulsmiller on 3/11/21.
//

#include <kvcg_logging.h>

int LOG_LEVEL = TRACE;

int main() {

    LOG(ERROR) << "Error";

    LOG2<ERROR>() << "Error";
    LOG2<DEBUG>() << "Debug";
    LOG2<TRACE>() << "Trace";

    return 0;

}