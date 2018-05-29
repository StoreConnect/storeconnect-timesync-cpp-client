//
// Created by Adrien Jonquet on 29/05/2018.
//

#include <server_date.h>


server_date::server_date(std::string url) : url{url}, synchronizing{false} {
    try {
        // cache dir = current working dir; cache size = 100 KB
        pCache = easyhttpcpp::HttpCache::createCache(Poco::Path::current(), 1024 * 100);
        // a default http connection pool
        pConnectionPool = easyhttpcpp::ConnectionPool::createConnectionPool();
        // configure http cache and connection pool instance (optional but recommended)
        httpClientBuilder.setCache(pCache).setConnectionPool(pConnectionPool);
        // create http client
        pHttpClient = httpClientBuilder.build();
        // create a new request and execute synchronously
        pRequest = requestBuilder.setUrl(url).build();
        pCall = pHttpClient->newCall(pRequest);
    } catch (const std::exception &e) {
        std::cout << "Error occurred: " << e.what() << std::endl;
    }
}

void server_date::get_date() {
    // HTTP GET the url
    std::cout << "HTTP GET url: " << url << std::endl;
    try {
        easyhttpcpp::Response::Ptr pResponse = pCall->execute();
        if (!pResponse->isSuccessful()) {
            std::cout << "HTTP GET Error: (" << pResponse->getCode() << ")" << std::endl;
        } else {
            std::cout << "HTTP GET Success!" << std::endl;
        }
        // dump response
        dumpResponse(pResponse);
    } catch (const std::exception &e) {
        std::cout << "Error occurred: " << e.what() << std::endl;
    }
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
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    long long now_epoch = now_ms.time_since_epoch().count();
    return now_epoch + offset;
}

void server_date::sync() {

}