//
// Created by Adrien Jonquet on 29/05/2018.
//

#include <server_date.h>
#include <easyhttp_get.h>
#include <gtest/gtest.h>
#include <thread>

TEST(basic_test, two_plus_two_test) {
    EXPECT_EQ(2+2, 4);
}

TEST(basic_test, basic_http_request) {

    easyhttp_get http_get = *new easyhttp_get();

    server_date server_date_instance("http://www.google.com/", 10, 5, http_get);
    server_date_instance.offset_amortization_enabled(true);
    server_date_instance.auto_synchronize();
    long long server_now = server_date_instance.now();
    std::cout << "server_now: " << server_now << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    server_date_instance.stop_auto_synchronize();
    std::this_thread::sleep_for(std::chrono::seconds(10));
}