#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>
#include <fstream>
class Item
{
public:
    Item(const std::string&, const std::string&, const std::string& ,unsigned long, unsigned long, double, double, double);
    virtual ~Item() = default;
    virtual void print() = 0;
    virtual void printCSV(std::ofstream&) = 0;
private:
    friend class ActiveInventory;
protected:
    std::string name;
    std::string category;
    std::string sub_category;
    unsigned long quantity;
    unsigned long id;
    double sale_price;
    double buy_cost;
    double tax;
    double total_price;
    double profit;
};

#endif
