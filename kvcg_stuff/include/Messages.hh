/**
 * @file
 */

#include "data_t.hh"

#ifndef KVCG_MESSAGES_HH
#define KVCG_MESSAGES_HH

struct Response {

    Response(int id, data_t *res, bool ret, bool shouldFree = false) : requestID(id), result(res), retry(ret),
                                                               shouldFree_(shouldFree) {

    }

    Response() : requestID(-1), result(nullptr), shouldFree_(false) {

    }


    ~Response() {
        if (shouldFree_) {
            if (result) {
                delete[] result->data;
                delete result;
            }
        }
    }

    int requestID;
    bool retry;
    data_t *result;
    bool shouldFree_;
};

template<>
inline std::vector<char> serialize<Response>(Response r) {
    std::vector<char> bytes(sizeof(int) + sizeof(bool));
    memcpy(bytes.data(), (const char *) &r.requestID, sizeof(int));
    memcpy((bytes.data() + sizeof(int)), (const char *) &r.retry, sizeof(bool));
    std::vector<char> b2 = serialize(r.result);
    bytes.insert(bytes.end(), b2.begin(), b2.end());
    return bytes;
}

template<>
inline size_t serialize2<Response>(char *bytes, size_t size, Response r) {
    assert(size > sizeof(int) + sizeof(bool));
    memcpy(bytes, (const char *) &r.requestID, sizeof(int));
    memcpy((bytes + sizeof(int)), (const char *) &r.retry, sizeof(bool));
    return sizeof(int) + sizeof(bool) +
           serialize2(bytes + sizeof(int) + sizeof(bool), size - (sizeof(int) + sizeof(bool)), r.result);
}

template<>
inline Response deserialize<Response>(const std::vector<char> &bytes) {
    Response r;
    r.requestID = *(int *) bytes.data();
    r.retry = *(bool *) (bytes.data() + sizeof(int));
    std::vector<char> b2(bytes.begin() + sizeof(int) + sizeof(bool), bytes.end());
    r.result = deserialize<data_t *>(b2);
    return r;
}

template<>
inline Response deserialize2<Response>(const std::vector<char> &bytes, size_t &bytesConsumed) {
    bytesConsumed = 0;
    Response r;
    r.requestID = *(int *) bytes.data();
    bytesConsumed += sizeof(int);
    r.retry = *(bool *) (bytes.data() + bytesConsumed);
    bytesConsumed += sizeof(int) + sizeof(bool);
    std::vector<char> b2(bytes.begin() + bytesConsumed, bytes.end());
    size_t data_tBytesConsumed = 0;
    r.result = deserialize2<data_t *>(b2, data_tBytesConsumed);
    bytesConsumed += data_tBytesConsumed;
    return r;
}

template<>
inline Response deserialize2<Response>(const char *bytes, size_t size, size_t &bytesConsumed) {
    bytesConsumed = 0;
    Response r;
    r.requestID = *(int *) bytes;
    bytesConsumed += sizeof(int);
    r.retry = *(bool *) (bytes + bytesConsumed);
    bytesConsumed += sizeof(int) + sizeof(bool);
    size_t data_tBytesConsumed = 0;
    r.result = deserialize2<data_t *>(bytes + bytesConsumed, size - bytesConsumed, data_tBytesConsumed);
    bytesConsumed += data_tBytesConsumed;
    return r;
}


#endif //KVCG_MESSAGES_HH
