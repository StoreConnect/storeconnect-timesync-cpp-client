//
// Created by Adrien Jonquet on 29/05/2018.
//

#include <server_date.h>
#include <Poco/DateTime.h>
#include <thread>
#include <cstdlib>
#include <cmath>

#define ERROR "ERROR"

long long server_date::local_now() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    return now_ms.time_since_epoch().count();
}

long long server_date::date_from_string(std::string date_s) {
    std::tm tm = {};
    strptime(date_s.c_str(), "%a, %d %b %Y %T", &tm);
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return tp.time_since_epoch().count();
}

server_date::server_date(std::string url, int sample_count, int refresh_rate)
        : url{url}, sample_count{sample_count}, refresh_rate{refresh_rate}, auto_sync_enabled{false} {
    try {
        // cache dir = current working dir; cache size = 100 KB
        pCache = easyhttpcpp::HttpCache::createCache(Poco::Path::current(), 1024 * 100);
        // a default http connection pool
        pConnectionPool = easyhttpcpp::ConnectionPool::createConnectionPool();
        // configure http cache and connection pool instance (optional but recommended)
        httpClientBuilder.setCache(pCache).setConnectionPool(pConnectionPool);
        // create http client
        pHttpClient = httpClientBuilder.build();
    } catch (const std::exception &e) {
        std::cout << "Error occurred: " << e.what() << std::endl;
    }
}

void server_date::offset_amortization_enabled(bool enabled) {
    is_amortization_enabled = enabled;
}

void server_date::auto_synchronize() {
    auto_sync_enabled = true;
    std::thread auto_sync_th = std::thread([&] {
        while (auto_sync_enabled) {
            if (counter_for_refresh == 0) {
                counter_for_refresh = refresh_rate;
                synchronise_date_sync();
            } else {
                counter_for_refresh--;
            }

            if(is_amortization_enabled && target!=offset) {
                perform_offset_amortization();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            } else {
                counter_for_refresh = 0;
                std::this_thread::sleep_for(std::chrono::seconds(refresh_rate));
            }
        }
    });

    if (auto_sync_th.joinable()) {
        auto_sync_th.detach();
    }
}

void server_date::stop_auto_synchronize() {
    auto_sync_enabled = false;
}

std::string server_date::request_date() {
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
        // dump response
        //dumpResponse(pResponse);
    } catch (const std::exception &e) {
        std::cout << "Error occurred: " << e.what() << std::endl;
    }
    return date_res;
}

void server_date::dumpResponse(easyhttpcpp::Response::Ptr pResponse) {
    std::cout << "Http status code: " << pResponse->getCode() << std::endl;
    std::cout << "Http status message: " << pResponse->getMessage() << std::endl;
    std::cout << "Http response headers:\n" << pResponse->getHeaders()->toString() << std::endl;

    // dump response body if text
    const std::string contentType = pResponse->getHeaderValue("Content-Type", "");
    if (Poco::isubstr<std::string>(contentType, "text/html") != std::string::npos) {
        std::cout << "Http response body:\n" << pResponse->getBody()->toString() << std::endl;
    }
}

long long server_date::now() {
    return local_now() + offset;
}

void dump_result(std::string server_date_s,
                 long long server_date,
                 long long request_time,
                 long long response_time,
                 long offset,
                 double precision) {
    std::cout << std::endl
              << "server_date_s: " << server_date_s
              << "  server_date: " << server_date
              << "  request_time: " << request_time
              << "  response_time: " << response_time
              << "  offset: " << offset
              << "  precision: " << precision;
}

void server_date::synchronise_date_sync() {
    long long best_precision = 0;
    long long best_offset = 0;
    for (int i = 0; i < sample_count; i++) {
        long long request_time = local_now();
        std::string server_date_s = request_date();
        if (server_date_s != ERROR) {
            long long response_time = local_now();
            long long server_date = date_from_string(server_date_s);
            long long tmp_precision = (response_time - request_time) / 2;
            long long tmp_offset = server_date + tmp_precision - response_time;
            dump_result(server_date_s, server_date, request_time, response_time, tmp_offset, tmp_precision);
            if (i == 0 || tmp_precision <= best_precision) {
                best_offset = tmp_offset;
                best_precision = tmp_precision;
            }
        }
    }

    if(is_amortization_enabled) {
        set_target(best_offset);
    } else {
        offset = best_offset;
        precision = best_precision;
    }
}

void server_date::set_target(long long int newOffset) {
    target = newOffset;
    long delta = target - offset;
    if (delta > amortization_threshold) {
        offset = target;
    }
}

void server_date::perform_offset_amortization() {

    // Don't let the delta be greater than the amortization_rate in either
    // direction.
    long delta = std::max(amortization_rate, std::min<signed long>(amortization_rate, target - offset));

    offset += delta;

    std::cout << "amortized offset: " << offset << std::endl;
}

double server_date::get_precision() {
    double d = target - offset;
    return precision + std::fabs(d);
}

double server_date::get_offset() {
    return offset;
}
