#include "NonPerishableItem.hpp"

NonPerishableItem::NonPerishableItem(const std::string& nm, unsigned int qty, unsigned int idd, double price, double cost, double tx)
: Item(nm, qty, idd, price, cost, tx)
{

}

void NonPerishableItem::print()
{
    std::cout << "ID: " << id << " Item: " << name << std::endl;
    std::cout << "In-Stock: " << quantity << std::endl;
    std::cout << "Stocking/Purchase Cost: " << buy_cost << std::endl;
    std::cout << "Sale Price: " << sale_price << std::endl;
    std::cout << "Tax on Item: " << tax * sale_price << std::endl;
    std::cout << "Profit per unit sold: " << profit << std::endl;
}

NonPerishableItem::~NonPerishableItem()
{

}