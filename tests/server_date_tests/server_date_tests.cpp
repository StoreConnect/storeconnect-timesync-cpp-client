//
// Created by Adrien Jonquet on 29/05/2018.
//

#include <server_date.h>
#include <gtest/gtest.h>

TEST(basic_test, two_plus_two_test) {
    EXPECT_EQ(2+2, 4);
}

TEST(basic_test, basic_http_request) {
    server_date server_date_instance("http://www.google.com");
    server_date_instance.sync();
}