//
// Created by Michal Gasztold on 01/06/2018.
//

#ifndef EASYHTTP_GET_H
#define EASYHTTP_GET_H

#include "easyhttpcpp/EasyHttp.h"
#include <http_get_interface.h>
#include <iostream>

class easyhttp_get : public http_get_interface {

public:
    easyhttp_get();

    std::string get(const std::string &url) {
        std::string date_res = ERROR;
        try {
            // create a new request and execute synchronously
            easyhttpcpp::Request::Ptr pRequest = requestBuilder.setUrl(url).build();
            easyhttpcpp::Call::Ptr pCall = pHttpClient->newCall(pRequest);
            easyhttpcpp::Response::Ptr pResponse = pCall->execute();
            if (!pResponse->isSuccessful()) {
                std::cout << "HTTP GET Error: (" << pResponse->getCode() << ")" << std::endl;
            } else {
                std::string date = pResponse->getHeaders()->getValue("Date", "NOT_FOUND");
                if (date != "date") {
                    date_res = date;
                }
            }
        } catch (const std::exception &e) {
            std::cout << "Error occurred: " << e.what() << std::endl;
        }
        return date_res;
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
