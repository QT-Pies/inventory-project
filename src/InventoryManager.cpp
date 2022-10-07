#include <iostream>
#include <string>
#include <fstream>
#include "InventoryManager.hpp"

InventoryManager::InventoryManager(const bool cli)
{
	command_line = cli;
}

InventoryManager::~InventoryManager()
{
	/* using smart pointer for active inventory so no deletion neccessary */
}

/* gets command line input from user and calls methods from active inventory class */
int InventoryManager::userInput()
{
	char argument;
	std::string name, category, value;
	unsigned long id; 
	
	if (command_line == false) {
        fprintf(stderr, "Command line is currently set to false\n");
        return -1;
    }
	
	std::cout << "\n(A)dd, (R)emove, (U)pdate, or (Q)uit: ";
	std::cin >> argument;	

	/* switch on argument specified from user and then prompt them accordingly for further input */
	switch(argument)
	{
		case 'A':
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			
			std::cout << "Name Perishable/NonPerishable ID: ";
			std::cin >> name >> category >> id;

			if (active_inventory->addItem(name, category, id) != -1) {
				std::cout << "Added " << name << " of type " << category << std::endl;
			}
			break;

		case 'R':
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			std::cout << "Name: ";
			std::cin >> name;

			if (active_inventory->removeItem(name) != -1) {
				std::cout << "Removed " << name << std::endl;
			} 
			break;

		case 'U':
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			
			std::cout << "Name Field Value: ";
			std::cin >> name >> category >> value;
			
			if (active_inventory->updateItem(name, category, value) != -1) {
				std::cout << "Updated " << category << " of " << name << " to " << value << std::endl;
			}
			break;
		case 'Q':
			printf("Quitting\n");
			return -1;
		default:
			std::cout << "Usage: <(A)dd | (R)emove | (U)pdate>" << std::endl;
			break;
	}

	std::cin.clear();
	std::cin.ignore(10000, '\n');
    
	return 0;
}

void InventoryManager::readCSVFile(const std::string &file)
{

	std::string name, str_id, cat, sub_cat, str_qty, str_sale_price;
	std::string str_tax, str_total_price, str_buy_cost, str_profit, exp; 
	
	unsigned long qty, id;
	double sale_price, tax, total_price, buy_cost, profit;
	
	std::ifstream csv_file(file);

	if(!csv_file.is_open()) std::cout << "ERROR: File Open" << '\n';
	
	while(csv_file.good()){

		getline(csv_file, name, ',');
		getline(csv_file, str_id, ',');
		id = stoul(str_id);
		getline(csv_file, cat, ',');
		getline(csv_file, sub_cat, ',');
		getline(csv_file, str_qty, ',');
		qty = stoul(str_qty);
		getline(csv_file, str_sale_price, ',');
		sale_price = stod(str_sale_price);
		getline(csv_file, str_tax, ',');
		tax = stod(str_tax);
		getline(csv_file, str_total_price, ',');
		total_price = stod(str_total_price);
		getline(csv_file, str_buy_cost, ',');
		buy_cost = stod(str_buy_cost);
		getline(csv_file, str_profit, ',');
		profit = stod(str_profit);
		getline(csv_file, exp, '\n');
		
		if(name == "Name") continue;

		if (active_inventory->addItem(name, cat, id) != -1) {
			std::cout << "Added " << name << " of type " << cat << std::endl;
		}
		active_inventory->addItem(name, cat, id);
		
	}
}
