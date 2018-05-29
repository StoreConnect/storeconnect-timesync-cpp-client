cmake_minimum_required(VERSION 3.9)
project(server_date)

set(SOURCE_FILES
        src/server_date.cpp)

include_directories(src)

add_library(server_date ${SOURCE_FILES})
