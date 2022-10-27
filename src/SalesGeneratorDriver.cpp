#include "SalesGenerator.hpp"

int main() {
    SalesGenerator generator("CSVInput/backorder_test.csv", "12/28/1999");

    generator.generateTransactions(10);

    return 0;
}