//
// Created by Adrien Jonquet on 29/05/2018.
//

#include <server_date.h>
#include <Poco/DateTime.h>

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

server_date::server_date(std::string url, int sample_count) : url{url}, synchronizing{false},
                                                              sample_count{sample_count} {
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

std::string server_date::request_date() {
    std::string date_res = ERROR;
    // HTTP GET the url
    std::cout << "HTTP GET url: " << url << std::endl;
    try {
        // create a new request and execute synchronously
        easyhttpcpp::Request::Ptr pRequest = requestBuilder.setUrl(url).build();
        easyhttpcpp::Call::Ptr pCall = pHttpClient->newCall(pRequest);
        easyhttpcpp::Response::Ptr pResponse = pCall->execute();
        if (!pResponse->isSuccessful()) {
            std::cout << "HTTP GET Error: (" << pResponse->getCode() << ")" << std::endl;
        } else {
            std::cout << "HTTP GET Success!" << std::endl;
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
                 double offset,
                 double precision) {
    std::cout << std::endl
              << "server_date_s: " << server_date_s
              << "  server_date: " << server_date
              << "  request_time: " << request_time
              << "  response_time: " << response_time
              << "  offset: " << offset
              << "  precision: " << precision
              << std::endl << std::endl;
}

void server_date::synchronise_date_sync() {
    long long best_precision;
    long long best_offset;
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
    offset = best_offset;
    precision = best_precision;
}

