#ifndef NONPERISHABLEITEM_HPP
#define NONPERISHABLEITEM_HPP

#include "Item.hpp"

class NonPerishableItem : private Item
{
public:
    NonPerishableItem(const std::string&, unsigned int, unsigned int, double, double, double);
    ~NonPerishableItem();
    void print();
};

#endif