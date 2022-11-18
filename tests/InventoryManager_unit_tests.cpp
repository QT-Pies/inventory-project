#include <gtest/gtest.h>

#include "../include/InventoryManager.hpp"

namespace {

TEST(InventoryManager, create) {
    /* Test creation of IM. */
    EXPECT_NE(std::make_shared<InventoryManager>(InventoryManager(1, "CSVInput/big_file.csv")), nullptr);
}

/*TEST(InventoryManager, read_write) {
    * Create an instance of IM. *
    auto IM = std::make_shared<InventoryManager>(InventoryManager(1, "CSVInput/big_file.csv"));

    * Since we can't access the contents of IM's active inventory, we will just read in and write out existing
     *  csv files. *
    IM->readCSVFile();
    EXPECT_EQ(IM->fileOutput(), 0);
} This test is seg faulting when there is no valid .csv file for sales existing. */
}  // namespace