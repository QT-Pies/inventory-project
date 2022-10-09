#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include "ActiveInventory.hpp"

class InventoryManager
{
public:
	InventoryManager(const bool);
	~InventoryManager();
	int userInput();
<<<<<<< HEAD
	void readCSVFile(const std::string&);
=======
>>>>>>> 5c926920398a41f6d9eb76658e21c4c6b541b208
	int fileOutput();
private:
	bool command_line;
	std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
	std::string file_name;
};

#endif
