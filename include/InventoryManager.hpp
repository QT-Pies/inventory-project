#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include "ActiveInventory.hpp"

class InventoryManager
{
public:
	InventoryManager(bool);
	~InventoryManager();
	int userInput();
private:
	bool command_line;
	std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
};

#endif
