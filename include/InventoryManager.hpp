#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include "ActiveInventory.hpp"

class InventoryManager
{
public:
	InventoryManager(const bool, const std::string);
	~InventoryManager();
	int userInput();
	void readCSVFile();
	int fileOutput();
private:
	bool command_line;
	std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
	std::string file_name;
};

#endif
