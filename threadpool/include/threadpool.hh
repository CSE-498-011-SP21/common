//
// Created by dePaul Miller on 2/28/21.
//

#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <iostream>

#ifndef COMMON_THREADPOOL_HH
#define COMMON_THREADPOOL_HH

namespace cse498 {
    template<typename Arg_t>
    class threadpool {
    public:

        /**
         * Function type
         */
        using fn_t = std::function<void(Arg_t)>;

        /**
         * Create threadpool
         * @param f function
         * @param threads number of threads
         */
        threadpool(fn_t f, int threads) : fn(f), done(false) {
            for(int i = 0; i < threads; i++){
                pool.push_back(std::thread([this](){
                    this->run();
                }));
            }
        }

        ~threadpool() = default;

        /**
         * Enqueue request to threadpool
         * @param a request
         */
        void enqueue(Arg_t a){
            std::unique_lock<mtx_t> ul(mtx);
            q.push(a);
            cv.notify_one();
        }

        /**
         * Use to join threadpool
         */
        void join(){
            done = true;
            cv.notify_all();
            for(auto& t : pool){
                if(t.joinable())
                    t.join();
            }
        }

    private:

        using mtx_t = std::mutex;

        /**
         * What to run on each thread in the pool
         */
        void run(){
            while(!done) {
                Arg_t arg;
                std::unique_lock<mtx_t> ul(mtx);
                if (q.empty()) {
                    cv.wait(ul); // will wake when not empty or done = true
                }
                if(!q.empty()) {
                    arg = q.front();
                    q.pop();
                } else { // done = true
                    return;
                }
                ul.unlock();
                fn(arg);
            }
            while(true) {
                Arg_t arg;
                std::unique_lock<mtx_t> ul(mtx);
                if (q.empty()) {
                    return;
                }
                arg = q.front();
                q.pop();
                ul.unlock();
                fn(arg);
            }
        }

        std::vector<std::thread> pool;
        fn_t fn;
        std::queue<Arg_t> q;
        std::condition_variable cv;
        mtx_t mtx;
        std::atomic<bool> done;
    };
}

#endif //COMMON_THREADPOOL_HH
