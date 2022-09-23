#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>

class Item
{
public:
    Item(const std::string&, const std::string&, unsigned int, unsigned int, double, double, double);
    virtual ~Item() = default;
    virtual void print() = 0;
private:
    friend class ActiveInventory;
protected:
    std::string name;
    std::string sub_category;
    unsigned int quantity;
    unsigned int id;
    double sale_price;
    double buy_cost;
    double tax;
    double total_price;
    double profit;
};

#endif