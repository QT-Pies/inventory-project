#include "PerishableItem.hpp"

/*
 * Constructor for PerishableItem; calls base Item constructor, initializes expiration_date member.
*/
PerishableItem::PerishableItem(const std::string& nm, const std::string& cat, unsigned int qty, unsigned int idd, double price, double cost, double tx, const std::string& exp)
: Item(nm, cat, qty, idd, price, cost, tx), expiration_date(Date(exp))
{
}

/*
 * Prints out the item information to standard output.
*/
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

/* print out item in csv format */
void PerishableItem::printCSV(std::ofstream& file)
{
	std::cout << "Enter" << std::endl;
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
	//file << expiration_date.string_date << std::endl;
	
}

/*
 * Destructor; empty implementation, but needed to shut compiler up.
*/
PerishableItem::~PerishableItem()
{
    
}