#ifndef PERISHABLEITEM_HPP
#define PERISHABLEITEM_HPP

#include "Item.hpp"
#include "Date.hpp"

class PerishableItem : private Item
{
public:
    PerishableItem(const std::string&, const std::string&, unsigned int, unsigned int, double, double, double, const std::string&);
    ~PerishableItem();
    void print();
protected:
    Date expiration_date;
};

#endif