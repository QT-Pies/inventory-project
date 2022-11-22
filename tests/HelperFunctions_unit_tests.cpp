#include <gtest/gtest.h>

#include "../include/HelperFunctions.hpp"

namespace {

TEST(HelperFunctions, toUnsignedLong) {
    /* Create a valid input and test it's output, then an invalid input. */
    EXPECT_EQ(toUnsignedLong("74"), 74);
    try {
        toUnsignedLong("-74");
    } catch (std::exception& e) {
        EXPECT_NE(e.what(), "-74");
    }
}

TEST(HelperFunctions, toFauxUnsignedDouble) {
    /* Create a valid input and test it's output, then an invalid input. */
    EXPECT_EQ(toFauxUnsignedDouble("74.74"), 74.74);
    try {
        toFauxUnsignedDouble("-74.9");
    } catch (std::exception& e) {
        EXPECT_NE(e.what(), "-74.9");
    }
}

TEST(HelperFunctions, lowerCaseString) {
    /* Create a valid input and test it's output. */
    std::string test = "APPLE";
    lowerCaseString(test);
    EXPECT_EQ(test, "apple");
}
}  // namespace