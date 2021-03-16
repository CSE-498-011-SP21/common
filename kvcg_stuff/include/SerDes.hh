//
// Created by depaulsmiller on 3/16/21.
//

#include <cassert>
#include <cstdlib>

#ifndef COMMON_SERDES_HH
#define COMMON_SERDES_HH

template<typename T>
inline std::vector<char> serialize(T t){
    exit(1);
}

template<typename T>
inline T deserialize(const std::vector<char>& v){
    exit(1);
}

#endif //COMMON_SERDES_HH
