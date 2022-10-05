#ifndef NONPERISHABLEITEM_HPP
#define NONPERISHABLEITEM_HPP

#include "Item.hpp"

class NonPerishableItem : public Item
{
public:
    NonPerishableItem(const std::string&, const std::string&, unsigned int, unsigned int, double, double, double);
    ~NonPerishableItem() override;
    void print() override;
private:
    friend class ActiveInventory;
};

#endif