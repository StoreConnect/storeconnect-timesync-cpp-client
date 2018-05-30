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
    void offset_amortization_enabled(bool enabled);
    double get_precision();
    double get_offset();

private:
    void dumpResponse(easyhttpcpp::Response::Ptr pResponse);
    std::string request_date();
    long long date_from_string(std::string date_s);
    long long local_now();
    void set_target(long long int offset);
    void perform_offset_amortization();

    std::string url;
    int sample_count;

    double precision;
    long offset;

    int counter_for_refresh = 0;
    int refresh_rate;

    long amortization_threshold = 2000; //ms
    long amortization_rate = 25;
    long target;
    bool is_amortization_enabled = false;

    easyhttpcpp::HttpCache::Ptr pCache;
    easyhttpcpp::ConnectionPool::Ptr pConnectionPool;
    easyhttpcpp::EasyHttp::Builder httpClientBuilder;
    easyhttpcpp::Request::Builder requestBuilder;
    easyhttpcpp::EasyHttp::Ptr pHttpClient;
};

#endif //LOCATION_MULTILATERATION_H