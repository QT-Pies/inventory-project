#ifndef PERISHABLEITEM_HPP
#define PERISHABLEITEM_HPP

#include "Item.hpp"
#include "Date.hpp"

class PerishableItem : public Item
{
public:
    PerishableItem(const std::string&, const std::string&, unsigned int, unsigned int, double, double, double, const std::string&);
    ~PerishableItem() override;
    void print() override;
private:
    friend class ActiveInventory;
protected:
    Date expiration_date;
};

#endif