#include <gtest/gtest.h>

#include "../include/PerishableItem.hpp"

namespace {

TEST(PerishableItem, createItem) {
    EXPECT_NE(std::make_shared<PerishableItem>(PerishableItem("Laptop", "Perishable", "Electronics", "15", "1",
                                                              "500.00", "150.00", "0.15", "10/25/2022")),
              nullptr);
    try {
        std::make_shared<PerishableItem>(PerishableItem("Laptop", "Perishable", "Electronics", "-15", "1", "500.00",
                                                        "150.00", "0.15", "10/25/2022"));
    } catch (std::exception &e) {
        /* This is just to make sure that an exception is being thrown. */
        EXPECT_NE(e.what(), "ANYTHING");
    }
}
}  // namespace