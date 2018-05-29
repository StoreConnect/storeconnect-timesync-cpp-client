cmake_minimum_required(VERSION 3.9)

include_directories(${server_date_SOURCE_DIR}/src)

add_executable(run_server_date_tests server_date_tests.cpp)

target_link_libraries(run_server_date_tests server_date)