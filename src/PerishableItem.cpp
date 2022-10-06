#include "PerishableItem.hpp"

PerishableItem::PerishableItem(const std::string& nm, const std::string& cat, unsigned long qty, unsigned long idd, double price, double cost, double tx, const std::string& exp)
: Item(nm, cat, qty, idd, price, cost, tx), expiration_date(Date(exp))
{
}

void PerishableItem::print()
{
    std::cout << "ID: " << id << " Item: " << name << std::endl;
    std::cout << "Expiration Date: " << expiration_date.string_date << std::endl;
    std::cout << "In-Stock: " << quantity << std::endl;
    std::cout << "Stocking/Purchase Cost: " << buy_cost << std::endl;
    std::cout << "Sale Price: " << sale_price << std::endl;
    std::cout << "Tax on Item: " << tax * sale_price << std::endl;
    std::cout << "Profit per unit sold: " << profit << std::endl;
}

PerishableItem::~PerishableItem()
{
    
}