<<<<<<< HEAD
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
=======
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
>>>>>>> 646baff9e088b4c0dd7310412708090615e93b60
