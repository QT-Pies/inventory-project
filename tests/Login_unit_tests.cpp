#include <gtest/gtest.h>

#include "../include/Login.hpp"

namespace {

TEST(Login, createUser) {
    /* Test creation of users with valid and invalid input. */
    Login login = Login();
    EXPECT_EQ(login.createUser("Jon", "12345", "owner"), true);
    EXPECT_EQ(login.createUser("Jon", "12345", "Baconator"), false);

    EXPECT_EQ(login.outputCSV(), true);
    EXPECT_NE(login.verifyUser("Jon", "12345"), nullptr);
}
}  // namespace