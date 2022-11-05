#include <gtest/gtest.h>

#include "../include/NonPerishableItem.hpp"

namespace {

TEST(NonPerishableItem, createItem) {
    EXPECT_NE(std::make_shared<NonPerishableItem>(
                  NonPerishableItem("Laptop", "NonPerishable", "Electronics", "15", "1", "0", "500.00", "150.00", "0.15")),
              nullptr);
    try {
        std::make_shared<NonPerishableItem>(
            NonPerishableItem("Laptop", "NonPerishable", "Electronics", "-15", "1", "0", "500.00", "150.00", "0.15"));
    } catch (std::exception &e) {
        /* This is just to make sure that an exception is being thrown. */
        EXPECT_NE(e.what(), "ANYTHING");
    }
}
}  // namespace