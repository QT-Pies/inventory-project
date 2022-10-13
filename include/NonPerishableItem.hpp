#ifndef NONPERISHABLEITEM_HPP
#define NONPERISHABLEITEM_HPP

#include "Item.hpp"

class NonPerishableItem : public Item
{
public:
    NonPerishableItem(const std::string&, const std::string&, const std::string&, unsigned long, unsigned long, double, double, double);
    ~NonPerishableItem() override;
    void print() override;
    void printCSV(std::ofstream&) override;
private:
    friend class ActiveInventory;
};

#endif
