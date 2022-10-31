#include <gtest/gtest.h>

#include "../include/Date.hpp"

namespace {

TEST(Date, create) {
    Date date = Date("10/22/2020");
    EXPECT_EQ(date.day, 22);
    EXPECT_EQ(date.month, 10);
    EXPECT_EQ(date.year, 2020);
}
}  // namespace