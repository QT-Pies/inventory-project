#include <gtest/gtest.h>

#include "../tests/ActiveInventory_unit_tests.cpp"
#include "../tests/Date_unit_tests.cpp"
#include "../tests/HelperFunctions_unit_tests.cpp"
#include "../tests/InventoryManager_unit_tests.cpp"
#include "../tests/Logger_unit_tests.cpp"
#include "../tests/Login_unit_tests.cpp"
#include "../tests/NonPerishableItem_unit_tests.cpp"
#include "../tests/PerishableItem_unit_tests.cpp"
#include "../tests/Sales_unit_tests.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}