#ifndef CSVENTRY_HPP
#define CSVENTRY_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class InventoryGenerator;
class SalesGenerator;
class MockSale;
class MockTransaction;

class CSVEntry {
    friend class InventoryGenerator;
    friend class SalesGenerator;
    friend class MockSale;
    friend class MockTransaction;

   public:
    CSVEntry();

    /*
     * @brief Construct a CSVEntry from a line from CSV file.
     * @param std::string Line to parse
     */
    CSVEntry(std::string);

    /*
     * @brief Prints the entry out to an ostream in CSV format
     * @param std::ostream& ostream to output to (std::cout | std::ofstream)
     */
    void printEntry(std::ostream&);

   protected:
    std::string name;
    std::string category;
    std::string sub_category;
    int quantity;
    int backorder;
    int id;
    double sale_price;
    double buy_cost;
    double tax;
    double total_price;
    double profit;
    std::string expiration_date;
};

#endif