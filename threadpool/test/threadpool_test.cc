//
// Created by dePaul Miller on 2/28/21.
//

#include <threadpool.hh>
#include <cassert>
#include <iostream>

int main(){
    std::atomic<int> sum;
    sum = 0;
    cse498::threadpool<int> t([&sum](int i){
        sum += i;
    }, 4);

    for(int i = 0; i < 100; i++){
        t.enqueue(1);
    }
    t.join();
    std::cerr << sum << std::endl;
    assert(sum == 100);
    return 0;
}