//
// Created by depaulsmiller on 3/16/21.
//

#include <Messages.hh>
#include <RequestWrapper.hh>
#include <iostream>

int main() {

    data_t *d = new data_t(3);
    d->data[0] = 'h';
    d->data[1] = 'i';
    d->data[2] = '\0';

    auto b = serialize(d);

    auto d2 = deserialize<data_t *>(b);

    std::cerr << d->data << std::endl;
    std::cerr << d2->data << std::endl;

    if (strcmp(d2->data, d->data) != 0)
        return 1;

    Response r;
    r.result = d;
    r.retry = true;
    r.requestID = 10;

    auto sr = serialize(r);

    auto r2 = deserialize<Response>(sr);

    if (r.retry != r2.retry)
        return 2;

    if (r.requestID != r2.requestID)
        return 3;

    if (strcmp(r.result->data, r2.result->data) != 0)
        return 4;

    RequestWrapper<unsigned long long, data_t *> w;
    w.requestInteger = 10;
    w.value = d;
    w.key = 11;
    w.endRange = 12;

    char* sw = new char[4096];

    size_t sizeWritten = serialize2(sw, 4096, w);

    size_t bytesConsumed = 0;

    auto w2 = deserialize2<RequestWrapper<unsigned long long, data_t *>>(sw, 4096, bytesConsumed);

    if (w.requestInteger != w2.requestInteger) {
        std::cerr << w.requestInteger << " != " << w2.requestInteger << std::endl;
        return 5;
    }

    if (strcmp(w.value->data, w2.value->data) != 0)
        return 6;

    if (w.key != w2.key)
        return 7;

    if (bytesConsumed != sizeWritten)
        return 8;

    if(w.endRange != w2.endRange)
        return 9;

    delete[] sw;

    return 0;
}