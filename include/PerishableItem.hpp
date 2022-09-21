#ifndef PERISHABLEITEM_HPP
#define PERISHABLEITEM_HPP

#include "Item.hpp"

class PerishableItem : private Item
{
public:
    PerishableItem(const std::string&, unsigned int, unsigned int, double, double, double, const std::string&);
    ~PerishableItem();
    void print();
protected:
    std::string expiration_date;
};

#endif