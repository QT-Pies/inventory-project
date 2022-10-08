#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "ActiveInventory.hpp"

class InventoryManager
{
public:
	InventoryManager(const bool, const std::string);
	~InventoryManager();
	int userInput();
	void readCSVFile(const std::string&);
	int fileOutput();
private:
	bool command_line;
	std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
	std::string file_name;
};

#endif
