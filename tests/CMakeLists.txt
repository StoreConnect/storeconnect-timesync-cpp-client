cmake_minimum_required(VERSION 3.9)
project(tests)

add_subdirectory(lib/googletest)
add_subdirectory(server_date_tests)

include_directories(${googletest_SOURCE_DIR}/include ${googletest_SOURCE_DIR} ${server_date_SOURCE_DIR}/src)

add_executable(run_tests server_date_tests/server_date_tests.cpp)

target_link_libraries(run_tests server_date gtest gtest_main)
