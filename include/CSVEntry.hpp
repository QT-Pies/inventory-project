#ifndef CSVENTRY_HPP
#define CSVENTRY_HPP

#include <string>
#include <iostream>

/* Forward declaration of InventoryGenerator */
class InventoryGenerator;

class CSVEntry
{
friend class InventoryGenerator;
public:
    /* Constructor; empty constructor */
    CSVEntry();

    /* 
     * Prints the entry out to standard output in CSV format 
     * @param std::ostream& ostream to output to (std::cout | std::ofstream)
     */
    void printEntry(std::ostream&);
protected:
    std::string name;
    std::string category;
    std::string sub_category;
    int quantity;
    int id;
    double sale_price;
    double buy_cost;
    double tax;
    double total_price;
    double profit;
    std::string expiration_date;
};

#endif