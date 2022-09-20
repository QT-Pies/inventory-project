#include "PerishableItem.hpp"

PerishableItem::PerishableItem(const std::string& nm, unsigned int qty, unsigned int idd, double price, double cost, double tx, const std::string& exp)
: Item(nm, qty, idd, price, cost, tx), expiration_date(exp)
{
}

void PerishableItem::print()
{
    ;
}

PerishableItem::~PerishableItem()
{
    //
}