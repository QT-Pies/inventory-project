#include <gtest/gtest.h>

#include "../include/Sales.hpp"

namespace {

TEST(Sales, createSales) {
    /* Create the saleslist, a sale, and a transaction. */
    auto saleList1 = new SaleList();
    auto sale = new Sale(10, 10, 10, 50.50);
    auto tran = new Transaction(1, "Me", "You", 2020, 10, 25);

    EXPECT_NE(saleList1, nullptr);
    EXPECT_NE(sale, nullptr);
    EXPECT_NE(tran, nullptr);
}

TEST(Sales, addTransactions) {
    /* Create the saleslist and add transactions. */
    auto saleList1 = new SaleList();

    saleList1->newTransaction(1, "Me", "You", 2020, 10, 25);
    saleList1->newTransaction(2, "Me", "You", 2020, 10, 25);
    saleList1->newTransaction(3, "Me", "You", 2020, 10, 25);
}

TEST(Sales, write_read) {
    /* Create the saleslist and open a file to read/write from. */
    auto saleList1 = new SaleList();
    saleList1->loadSales("CSVInput/big_file.csv");

    /* Add transactions to the list then print them to file. */
    saleList1->newTransaction(1, "Me", "You", 2020, 10, 25);
    saleList1->newTransaction(2, "Me", "You", 2020, 10, 25);
    saleList1->newTransaction(3, "Me", "You", 2020, 10, 25);

    saleList1->save();
}
}  // namespace