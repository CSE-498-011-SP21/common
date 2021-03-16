/**
 * @file
 */

#include "data_t.hh"

#ifndef KVCG_MESSAGES_HH
#define KVCG_MESSAGES_HH

struct Response {

    Response(int id, data_t *res, bool ret) : requestID(id), result(res), retry(ret) {

    }

    Response() : requestID(-1) {

    }


    ~Response() {}

    int requestID;
    bool retry;
    data_t *result;
};

inline std::vector<char> serialize(const Response& r) {
    std::vector<char> bytes(sizeof(int) + sizeof(bool));
    memcpy(bytes.data(), (const char *) &r.requestID, sizeof(int));
    memcpy((bytes.data() + sizeof(int)), (const char*)&r.retry, sizeof(bool));
    std::vector<char> b2 = serialize(r.result);
    bytes.insert(bytes.end(), b2.begin(), b2.end());
    return bytes;
}

inline Response deserialize_response(const std::vector<char> &bytes) {
    Response r;
    r.requestID = *(int*)bytes.data();
    r.retry = *(bool*)(bytes.data() + sizeof(int));
    std::vector<char> b2(bytes.begin() + sizeof(int) + sizeof(bool), bytes.end());
    r.result = deserialize_data(b2);
    return r;
}


#endif //KVCG_MESSAGES_HH
