#include "SalesGenerator.hpp"

int main() {
    SalesGenerator generator;

    generator.readInventory("CSVInput/little_file.csv");

    return 0;
}