//
// Created by Michal Gasztold on 01/06/2018.
//

#ifndef EASYHTTP_GET_H
#define EASYHTTP_GET_H

#include "easyhttpcpp/EasyHttp.h"
#include <http_get_interface.h>
#include <iostream>
#include "third_party/json.hpp"

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
                nlohmann::json body_json = nlohmann::json::parse(pResponse->getBody()->toString());
                long now = body_json["time_millis"];
                std::string now_string = std::to_string(now);
                if (now_string != "date") {
                    date_res = now_string;
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
