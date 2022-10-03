#include <iostream>
#include <string>
#include "InventoryManager.hpp"

InventoryManager::InventoryManager(bool cli)
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
	
	if (command_line == false) {
        std::cout << "Command line is currently set to false" << std::endl;
        return -1;
    }

	std::cout << "(A)dd, (R)emove, or (U)pdate item: ";
	std::cin >> argument;	

	/* switch on argument specified from user and then prompt them accordingly for further input */
	switch(argument)
	{
		case 'A':
            std::cout << "Perishable/Nonperishable Name: ";
			std::cin >> category >> name;

			if (active_inventory->addItem(name, category) != -1) {
				std::cout << "\nAdded " << name << " of type " << category << std::endl;
			} else {
                return -1;
            }
			break;

		case 'R':
			std::cout << "\nName: ";
			std::cin >> name;

			if (active_inventory->removeItem(name) != -1) {
				std::cout << "\nRemoved " << name << std::endl;
			} else {
                return -1;
            }
			break;

		case 'U':
			std::cout << "\nName Field Value: ";
			std::cin >> name >> category >> value;
			
			if (active_inventory->updateItem(name, category, value) != -1) {
				std::cout << "\nUpdated " << category << " of " << name << " to " << value << std::endl;
			} else {
                return -1;
            }
			break;

		default:
			std::cout << "Usage: <(A)dd | (R)emove | (U)pdate>" << std::endl;
			break;
	}

    return 0;
}
