#include <gtest/gtest.h>

#include "../include/Logger.hpp"

namespace {
TEST(Logger, logLevelToString) {
    EXPECT_EQ(logLevelToString(LogLevel::TRACE), "TRACE");
    EXPECT_EQ(logLevelToString(LogLevel::DEBUG), "DEBUG");
    EXPECT_EQ(logLevelToString(LogLevel::INFO), "INFO");
    EXPECT_EQ(logLevelToString(LogLevel::WARN), "WARN");
    EXPECT_EQ(logLevelToString(LogLevel::ERROR), "ERROR");
    EXPECT_EQ(logLevelToString(LogLevel::FATAL), "FATAL");

    /* Since this requires actual LogLevel params, can't really test bad input. */
}

TEST(Logger, stringToLogLevel) {
    EXPECT_EQ(stringToLogLevel("TRACE"), LogLevel::TRACE);
    EXPECT_EQ(stringToLogLevel("DEBUG"), LogLevel::DEBUG);
    EXPECT_EQ(stringToLogLevel("INFO"), LogLevel::INFO);
    EXPECT_EQ(stringToLogLevel("WARN"), LogLevel::WARN);
    EXPECT_EQ(stringToLogLevel("ERROR"), LogLevel::ERROR);
    EXPECT_EQ(stringToLogLevel("FATAL"), LogLevel::FATAL);

    /* Test bad input */
    try {
        stringToLogLevel("EPICLOGLEVEL");
    } catch (std::exception& e) {
        EXPECT_EQ(e.what(), "Bad LogLevel value");
    }
}

/* This feels like enough testing, the Logger class doesn't return any values, so we'd just have to check for exceptions which should never get thrown. */

}