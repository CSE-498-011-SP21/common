//
// Created by dePaul Miller on 2/28/21.
//

#include <queue>
#include <functional>
#include <tbb/concurrent_queue.h>
#include <thread>
#include <vector>
#include <atomic>
#include <iostream>
#include <memory>

#ifndef COMMON_THREADPOOL_HH
#define COMMON_THREADPOOL_HH

namespace cse498 {

    class threadpool {
    public:

        /**
         * Function type
         */
        using fn_t = std::function<void()>;

        /**
         * Create threadpool
         * @param f function
         * @param threads number of threads
         */
        explicit threadpool(int threads);

        threadpool(const threadpool &) = delete;

        threadpool(threadpool &&) = delete;

        ~threadpool();

        /**
         * Submit request to threadpool
         * @param fn request
         */
        void submit(const fn_t &fn);

        /**
         * Waits for the queue to be empty and then joins
         */
        void join();

    private:
        using q_t = tbb::concurrent_queue<fn_t>;

        void run();

        std::vector<std::thread> pool;
        q_t q;
        std::atomic<bool> done;
    };
}

#endif //COMMON_THREADPOOL_HH
