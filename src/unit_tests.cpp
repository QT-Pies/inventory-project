#include <gtest/gtest.h>

#include "../tests/ActiveInventory_unit_tests.cpp"
#include "../tests/Date_unit_tests.cpp"
//#include "HelperFunctions_unit_tests.cpp"
//#include "InventoryGenerator_unit_tests.cpp"
//#include "InventoryGeneratorDriver_unit_tests.cpp"
//#include "InventoryManager_unit_tests.cpp"
//#include "Item_unit_tests.cpp"
//#include "Login_unit_tests.cpp"
//#include "NonPerishableItem_unit_tests.cpp"
//#include "PerishableItem_unit_tests.cpp"
//#include "Sales_unit_tests.cpp"
//#include "User_unit_tests.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}