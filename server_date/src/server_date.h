//
// Created by Adrien Jonquet on 29/05/2018.
//

#ifndef SERVER_DATE_H
#define SERVER_DATE_H


#include <string>
#include "models.h"
#include <iostream>
#include "http_get_interface.h"

class server_date {

public:
    server_date(std::string url, int sample_count, int refresh_rate, http_get_interface * http_interface);
    ~server_date() {
        delete_http_interface();
    }
    long long now();
    void synchronise_date_sync();
    void auto_synchronize();
    void offset_amortization_enabled(bool enabled);
    void stop_auto_synchronize();
    double get_precision();
    double get_offset();

private:
    std::string request_date();
    long long date_from_string(std::string date_s);
    long long local_now();
    void set_target(long long int offset);
    void perform_offset_amortization();

    void delete_http_interface() {
        delete http_get;
        http_get = 0;
    }

    std::string url;
    int sample_count;

    bool auto_sync_enabled;

    double precision;
    long offset = 0;

    int counter_for_refresh = 0;
    int refresh_rate;

    long amortization_threshold = 2000; //ms
    long amortization_rate = 25;
    long target;
    bool is_amortization_enabled = false;

    http_get_interface * http_get;
};

#endif //LOCATION_MULTILATERATION_H