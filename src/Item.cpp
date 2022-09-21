#include "Item.hpp"

/*
 * Constructor for base Item class; initializes data to given values.
 */
Item::Item(const std::string& nm, unsigned int qty, unsigned int idd, double price, double cost, double tx)
: name(nm), quantity(qty), id(idd), sale_price(price), buy_cost(cost), tax(tx)
{
    profit = sale_price - buy_cost;
    total_price = sale_price + (tax * sale_price);
}