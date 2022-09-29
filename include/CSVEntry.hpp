#ifndef CSVENTRY_HPP
#define CSVENTRY_HPP

#include <string>
#include <iostream>

class CSVGenerator;

class CSVEntry
{
friend class CSVGenerator;
public:
    CSVEntry();
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