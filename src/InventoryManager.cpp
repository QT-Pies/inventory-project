#include <iostream>
#include <string>
#include <fstream>
#include <map>
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
	unsigned int id; 
	
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

/* traverse active_memory and output content to file */
int InventoryManager::fileOutput()
{
	std::ofstream file;
	std::map<std::string, std::shared_ptr<Item> >::iterator mit;

	file.open(file_name);

	if (!file.is_open()) {
		fprintf(stderr, "File %s is unable to open", file_name.c_str());
		return -1;
	}

	file << "Name,ID,Category,Sub-Category,Quantity,Sale Price,Tax,Total Price,Buy Cost,Profit,Expiration Date" << std::endl;

	for (mit = active_inventory->inv_by_name.begin(); mit != active_inventory->inv_by_name.end(); mit++) {
		mit->second->printCSV(file);
		file << std::endl;
	}

	file.close();

	std::cout << "Inventory written to " << file_name << std::endl;
	return 0;
}