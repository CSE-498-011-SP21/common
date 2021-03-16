//
// Created by depaulsmiller on 3/16/21.
//

#include <Messages.hh>
#include <iostream>

int main(){

    data_t* d = new data_t(3);
    d->data[0] = 'h';
    d->data[1] = 'i';
    d->data[2] = '\0';

    auto b = serialize(d);

    auto d2 = deserialize_data(b);

    std::cerr << d->data << std::endl;
    std::cerr << d2->data << std::endl;

    if(strcmp(d2->data, d->data) != 0)
        return 1;

    Response r;
    r.result = d;
    r.retry = true;
    r.requestID = 10;

    auto sr = serialize(r);

    auto r2 = deserialize_response(sr);

    if(r.retry != r2.retry)
        return 2;

    if(r.requestID != r2.requestID)
        return 3;

    if(strcmp(r.result->data, r2.result->data) != 0)
        return 4;

    return 0;
}