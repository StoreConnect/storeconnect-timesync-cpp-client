//
// Created by Adrien Jonquet on 29/05/2018.
//

#ifndef SERVER_DATE_H
#define SERVER_DATE_H


#include <string>
#include <easyhttpcpp/Response.h>
#include "models.h"
#include <iostream>
#include "easyhttpcpp/EasyHttp.h"

class server_date {

public:
    server_date(std::string url, int sample_count, int refresh_rate);
    long long now();
    void synchronise_date_sync();
    void auto_synchronize();

private:
    void dumpResponse(easyhttpcpp::Response::Ptr pResponse);
    std::string request_date();
    long long date_from_string(std::string date_s);
    long long local_now();

    std::string url;
    int sample_count;

    double precision;
    double offset;

    int refresh_rate;

    easyhttpcpp::HttpCache::Ptr pCache;
    easyhttpcpp::ConnectionPool::Ptr pConnectionPool;
    easyhttpcpp::EasyHttp::Builder httpClientBuilder;
    easyhttpcpp::Request::Builder requestBuilder;
    easyhttpcpp::EasyHttp::Ptr pHttpClient;
};

#endif //LOCATION_MULTILATERATION_H