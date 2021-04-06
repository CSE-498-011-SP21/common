//
// Created by depaulsmiller on 3/16/21.
//

#include "SerDes.hh"
#include "data_t.hh"
#include <iostream>

#ifndef COMMON_REQUESTWRAPPER_HH
#define COMMON_REQUESTWRAPPER_HH

template<typename K, typename V>
struct RequestWrapper {
    K key;
    V value;
    unsigned requestInteger;
};

template<>
inline std::vector<char>
serialize<RequestWrapper<unsigned long long, data_t *>>(RequestWrapper<unsigned long long, data_t *> r) {
    std::vector<char> bytes(sizeof(unsigned long long));
    std::vector<char> bytes2(sizeof(unsigned));
    memcpy(bytes.data(), (const char *) &r.key, sizeof(unsigned long long));
    std::vector<char> v = serialize(r.value);
    memcpy(bytes2.data(), (const char *) &r.requestInteger, sizeof(unsigned));
    bytes.insert(bytes.end(), v.begin(), v.end());
    bytes.insert(bytes.end(), bytes2.begin(), bytes2.end());
    return bytes;
}

template<>
inline size_t
serialize2<RequestWrapper<unsigned long long, data_t *>>(char *bytes, size_t size,
                                                         RequestWrapper<unsigned long long, data_t *> r) {
    size_t offset = 0;
    memcpy(bytes, (const char *) &r.key, sizeof(unsigned long long));
    offset += sizeof(unsigned long long);
    offset += serialize2(bytes + offset, size - offset, r.value);
    memcpy(bytes + offset, (const char *) &r.requestInteger, sizeof(unsigned));
    offset += sizeof(unsigned);
    return offset;
}


template<>
inline RequestWrapper<unsigned long long, data_t *>
deserialize<RequestWrapper<unsigned long long, data_t *>>(const std::vector<char> &bytes) {

    RequestWrapper<unsigned long long, data_t *> r;
    r.key = *(unsigned long long *) bytes.data();
    std::vector<char> bytes2(bytes.begin() + sizeof(unsigned long long), bytes.end());
    r.value = deserialize<data_t *>(bytes2);
    r.requestInteger = *(unsigned *) (bytes.data() + bytes.size() - sizeof(unsigned));
    return r;
}

template<>
inline RequestWrapper<unsigned long long, data_t *>
deserialize2<RequestWrapper<unsigned long long, data_t *>>(const std::vector<char> &bytes, size_t &bytesConsumed) {
    bytesConsumed = 0;
    RequestWrapper<unsigned long long, data_t *> r;
    r.key = *(unsigned long long *) bytes.data();
    bytesConsumed += sizeof(unsigned long long);
    std::vector<char> bytes2(bytes.begin() + bytesConsumed, bytes.end());
    size_t data_tBytesConsumed = 0;
    r.value = deserialize2<data_t *>(bytes2, data_tBytesConsumed);
    bytesConsumed += data_tBytesConsumed;
    r.requestInteger = *(unsigned *) (bytes.data() + bytesConsumed);
    bytesConsumed += sizeof(unsigned);
    return r;
}

template<>
inline RequestWrapper<unsigned long long, data_t *>
deserialize2<RequestWrapper<unsigned long long, data_t *>>(const char *bytes, size_t size, size_t &bytesConsumed) {
    bytesConsumed = 0;
    RequestWrapper<unsigned long long, data_t *> r;
    r.key = *(unsigned long long *) bytes;
    bytesConsumed += sizeof(unsigned long long);
    size_t data_tBytesConsumed = 0;
    r.value = deserialize2<data_t *>(bytes + bytesConsumed, size - bytesConsumed, data_tBytesConsumed);
    bytesConsumed += data_tBytesConsumed;
    r.requestInteger = *(unsigned *) (bytes + bytesConsumed);
    bytesConsumed += sizeof(unsigned);
    return r;
}


#endif //COMMON_REQUESTWRAPPER_HH
