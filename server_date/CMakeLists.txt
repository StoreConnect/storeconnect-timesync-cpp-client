cmake_minimum_required(VERSION 3.9)

project(server_date)

set(SOURCE_FILES
        src/server_date.cpp
        src/easyhttp_get.cpp)

find_package(OpenSSL REQUIRED)
find_package(Poco REQUIRED Foundation Data DataSQLite Net NetSSL Crypto CONFIG)
find_package(easyhttpcpp REQUIRED CONFIG)

include_directories(src)
include_directories(src/third_party)

add_library(server_date ${SOURCE_FILES})

target_link_libraries(server_date
        easyhttpcpp::easyhttp
        Poco::Foundation
        Poco::Data Poco::DataSQLite
        Poco::Net Poco::NetSSL Poco::Crypto
        OpenSSL::SSL OpenSSL::Crypto
        )