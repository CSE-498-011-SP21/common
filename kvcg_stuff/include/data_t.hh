/**
 * @file
 */

#include <vector>
#include <cstring>
#include <cassert>
#include <SerDes.hh>

#ifndef KVCG_DATA_T_HH
#define KVCG_DATA_T_HH

struct data_t {

    data_t() : size(0), data(nullptr) {}

    data_t(size_t s) : size(s), data(new char[s]) {}

    /// Note this doesn't free the underlying data
    ~data_t() {}

    size_t size;
    char *data;

    inline data_t &operator=(const data_t &rhs) {
        this->size = rhs.size;
        this->data = rhs.data;
        return *this;
    }

    inline volatile data_t &operator=(const data_t &rhs) volatile {
        this->size = rhs.size;
        this->data = rhs.data;
        return *this;
    }

};

template<>
inline std::vector<char> serialize<data_t *>(data_t *data) {
    size_t numBytes = (data == nullptr ? sizeof(size_t) : sizeof(size_t) + data->size);
    std::vector<char> bytes(numBytes);
    if (data) {
        memcpy(bytes.data(), (const char *) &data->size, sizeof(size_t));
        memcpy((bytes.data() + sizeof(size_t)), data->data, data->size);
    } else {
        size_t tmp = 0;
        memcpy(bytes.data(), (const char *) &tmp, sizeof(size_t));
    }
    return bytes;
}

template<>
inline data_t *deserialize<data_t *>(const std::vector<char> &bytes) {
    size_t numBytes = *(size_t *) bytes.data();
    assert(bytes.size() >= numBytes + sizeof(size_t));
    if (numBytes == 0) {
        return nullptr;
    } else {
        data_t *data = new data_t(numBytes);
        memcpy(data->data, (bytes.data() + sizeof(size_t)), numBytes);
        return data;
    }
}

template<>
inline data_t *deserialize2<data_t *>(const std::vector<char> &bytes, size_t &bytesConsumed) {
    bytesConsumed = 0;
    size_t numBytes = *(size_t *) bytes.data();
    bytesConsumed += sizeof(size_t);
    assert(bytes.size() >= numBytes + sizeof(size_t));
    if (numBytes == 0) {
        return nullptr;
    } else {
        data_t *data = new data_t(numBytes);
        memcpy(data->data, (bytes.data() + sizeof(size_t)), numBytes);
        bytesConsumed += numBytes;
        return data;
    }
}

template<>
inline data_t *deserialize2<data_t *>(const char* bytes, size_t size, size_t &bytesConsumed) {
    bytesConsumed = 0;
    size_t numBytes = *(size_t *) bytes;
    bytesConsumed += sizeof(size_t);
    assert(size >= numBytes + sizeof(size_t));
    if (numBytes == 0) {
        return nullptr;
    } else {
        data_t *data = new data_t(numBytes);
        memcpy(data->data, (bytes + sizeof(size_t)), numBytes);
        bytesConsumed += numBytes;
        return data;
    }
}


#endif //KVCG_DATA_T_HH
