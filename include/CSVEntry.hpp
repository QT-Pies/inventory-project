#ifndef CSVENTRY_HPP
#define CSVENTRY_HPP

#include <iostream>
#include <string>

class InventoryGenerator;

class CSVEntry {
    friend class InventoryGenerator;

   public:
    CSVEntry();

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