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
	std::cout << "in read\n";
	std::string name, str_id, cat, sub_cat, qty, sale_price;
	std::string tax, total_price, buy_cost, profit, exp; 
	std::string tmp_line;

	unsigned long id;
	///double sale_price, tax, total_price, buy_cost, profit;
	
	std::ifstream csv_file(file);

	if(!csv_file.is_open()) std::cout << "ERROR: File Open" << '\n';
	
	/* This skips the first line for you. */
	std::getline(csv_file, tmp_line);

	while(csv_file.good()){

		/*reading in the csv info, converting types*/
		getline(csv_file, name, ',');

		/* The condition of the loop is checked once per loop, so if one of these breaks,
		 * all of them are still going to run.
		 * That should be fine, but I added a little check here for you that should exit the loop if
		 * we didn't read in a new name.
		*/
		if (!csv_file.good()) break;

		getline(csv_file, str_id, ',');
		id = std::stoul(str_id);
		getline(csv_file, cat, ',');
		getline(csv_file, sub_cat, ',');
		getline(csv_file, qty, ',');
		getline(csv_file, sale_price, ',');
		getline(csv_file, tax, ',');
		getline(csv_file, total_price, ',');
		getline(csv_file, buy_cost, ',');
		getline(csv_file, profit, ',');
		getline(csv_file, exp, '\n');

		/* Add the item to the inventory. */
		if (active_inventory->addItem(name, cat, id) != -1) {
			std::cout << "Added " << name << " of type " << cat << std::endl;
		} else {
			fprintf(stderr, "Failed to read in item %s with ID %lu.\n", name.c_str(), id);
		}

		/* Update all the item categories */
		active_inventory->updateItem(name, "sub_category", sub_cat);
		active_inventory->updateItem(name, "quantity", qty);
		active_inventory->updateItem(name, "sale_price", sale_price);
		active_inventory->updateItem(name, "buy_cost", buy_cost);
		active_inventory->updateItem(name, "tax", tax);
		active_inventory->updateItem(name, "total_price", total_price);
		active_inventory->updateItem(name, "profit", profit);
		active_inventory->updateItem(name, "expiration_date", exp);

		/* Test to see if we successfully read in item. */
		auto item_ptr = active_inventory->searchByName(name);
		if (item_ptr != NULL) {
			/* Remove this print once you verify that your function is working as you expect. */
    		item_ptr->print();
		} 
		else {
    		fprintf(stderr, "Failed to read item %s that we just created.\n", name.c_str());
		}
	}
}
