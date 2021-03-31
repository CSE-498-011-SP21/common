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
inline size_t serialize2(char* bytes, size_t size, T t){
    exit(1);
}

template<typename T>
inline T deserialize(const std::vector<char>& v){
    exit(1);
}

template<typename T>
inline T deserialize2(const std::vector<char>& v, size_t& bytesConsumed){
    exit(1);
}

template<typename T>
inline T deserialize2(const char* bytes, size_t size, size_t& bytesConsumed){
    exit(1);
}


#endif //COMMON_SERDES_HH
