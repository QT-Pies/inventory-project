#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include "ActiveInventory.cpp"

class InventoryManager
{
	public:
		inventoryManager(bool);
		~inventoryManager();
		int userInput();
	private:
		bool command_line;
		std::unique_ptr<ActiveInventory> active_inventory(new ActiveInventory());
};

#endif
