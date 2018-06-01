//
// Created by Michal Gasztold on 01/06/2018.
//

#include <easyhttpcpp/Response.h>
#include <iostream>
#include "easyhttp_get.h"
#include "easyhttpcpp/EasyHttp.h"

void dumpResponse(easyhttpcpp::Response::Ptr pResponse) {
    std::cout << "Http status code: " << pResponse->getCode() << std::endl;
    std::cout << "Http status message: " << pResponse->getMessage() << std::endl;
    std::cout << "Http response headers:\n" << pResponse->getHeaders()->toString() << std::endl;

    // dump response body if text
    const std::string contentType = pResponse->getHeaderValue("Content-Type", "");
    if (Poco::isubstr<std::string>(contentType, "text/html") != std::string::npos) {
        std::cout << "Http response body:\n" << pResponse->getBody()->toString() << std::endl;
    }
}

easyhttp_get::easyhttp_get() {
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
