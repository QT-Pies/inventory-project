#include "../include/Date.hpp"
#include <gtest/gtest.h>


namespace {

    TEST(Date, create) {

        Date date = Date("10/22/2020");
        EXPECT_EQ(date.day, 22);
        EXPECT_EQ(date.month, 10);
        EXPECT_EQ(date.year, 2020);

    }
}