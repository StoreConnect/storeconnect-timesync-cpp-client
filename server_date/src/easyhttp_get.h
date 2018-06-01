//
// Created by Michal Gasztold on 01/06/2018.
//

#ifndef EASYHTTP_GET_H
#define EASYHTTP_GET_H

#include "easyhttpcpp/EasyHttp.h"
#include <http_get_interface.h>

class easyhttp_get : public http_get_interface {

public:
    easyhttp_get();
    std::string get() {
        return "dupa";
    }

private:
    void dumpResponse(easyhttpcpp::Response::Ptr pResponse);

    easyhttpcpp::HttpCache::Ptr pCache;
    easyhttpcpp::ConnectionPool::Ptr pConnectionPool;
    easyhttpcpp::EasyHttp::Builder httpClientBuilder;
    easyhttpcpp::Request::Builder requestBuilder;
    easyhttpcpp::EasyHttp::Ptr pHttpClient;
};

#endif //EASYHTTP_GET_H
