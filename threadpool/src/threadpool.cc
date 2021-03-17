//
// Created by depaulsmiller on 3/17/21.
//

#include "threadpool.hh"

namespace cse498 {

    threadpool::threadpool(int threads) : done(false) {
        for (int i = 0; i < threads; i++) {
            pool.push_back(std::thread([this]() {
                this->run();
            }));
        }
    }

    threadpool::~threadpool() {
        if (!done) {
            done = true;
            for (auto &t: pool) {
                if (t.joinable())
                    t.join();
            }
        }
    }

    void threadpool::submit(const fn_t &fn) {
        q.push(fn);
    }

    void threadpool::join() {
        while (!q.empty());
        done = true;
        for (auto &t: pool) {
            if (t.joinable())
                t.join();
        }
    }

    void threadpool::run() {
        while (!done) {
            fn_t fn;
            if (q.try_pop(fn)) {
                fn();
            } else {
                std::this_thread::yield();
            }
        }
    }

}