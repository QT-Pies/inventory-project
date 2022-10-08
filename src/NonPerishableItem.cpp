#include "NonPerishableItem.hpp"

/* 
 * Constructor for NonPerishableItem; call's base class constructor.
*/
NonPerishableItem::NonPerishableItem(const std::string& nm, const std::string& cat, unsigned int qty, unsigned int idd, double price, double cost, double tx)
: Item(nm, cat, qty, idd, price, cost, tx)
{

}

/*
 * Prints out the item information to standard output.
*/
void NonPerishableItem::print()
{
    std::cout << "ID: " << id << " Item: " << name << std::endl;
    std::cout << "In-Stock: " << quantity << std::endl;
    std::cout << "Stocking/Purchase Cost: " << buy_cost << std::endl;
    std::cout << "Sale Price: " << sale_price << std::endl;
    std::cout << "Tax on Item: " << tax * sale_price << std::endl;
    std::cout << "Profit per unit sold: " << profit << std::endl;
}

/* print out item in csv format */
void NonPerishableItem::printCSV(std::ofstream& file) 
{
	file << name << ",";
	file << id << ",";
	file << category << ",";
	file << sub_category << ",";
	file << quantity << ",";
	file << sale_price << ",";
	file << tax << ",";
	file << total_price << ",";
	file << buy_cost << ",";
	file << profit << ",";
	file << "-1" << std::endl;
}

/*
 * Destructor; currently empty, but needs to be here to shut the compiler up.
*/
NonPerishableItem::~NonPerishableItem()
{

}