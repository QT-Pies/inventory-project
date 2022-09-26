#include <iostream>
#include <string>
#include "../include/InventoryManager.hpp"

InventoryManager::InventoryManager(bool cli)
{
	command_line = cli;
}

InventoryManager::~InventoryManager()
{
	/* using smart pointer for active inventory so no deletion neccessary */
}

/* gets command line input from user and calls methods from active inventory class */
void InventoryManager::userInput()
{
	std::string argument, name, category, value; 
	
	if (command_line == false) {
        std::cout << "Command line is currently set to false" << std::endl;
        return;
    }

	std::cout << "Add, Remove, or Update item: ";
	std::cin >> argument;	

	/* switch on argument specified from user and then prompt them accordingly for further input */
	switch(argument)
	{
		case "Add":
            std::cout << "Perishable/Nonperishable Name: ";
			std::cin >> category >> name;

			if (active_inventory->addItem(name, category) != -1) {
				std::cout << "\nAdded " << name << " of type " << category << std::endl;
			}
			break;

		case "Remove":
			std::cout << "\nName: ";
			std::cin >> name;

			if (active_inventory->removeItem(name) != -1) {
				std::cout << "\nRemoved " << name << std::endl;
			}
			break;

		case "Update":
			std::cout << "\nName Field Value: ";
			std::cin >> name >> category >> value;
			
			if (active_inventory->updateItem(name, category, value) != -1) {
				std::cout << "\nUpdated " << category << " of " << name << " to " << value << std::endl;
			}
			break;

		default:
			std::cout << "Usage: <Add | Remove | Update>" << std::endl;
			break;
	}
}
