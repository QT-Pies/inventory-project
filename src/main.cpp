#include <iostream>
#include "../include/InventoryManager.hpp"

int main(int argc, char**argv){

	bool command_line;

	if (argc == 2) {
		command_line = argv[1];
	} else {
		std::cout << "Usage: bin/main command_line" << std::endl;
		return -1;
	}

	InventoryManager im(command_line);
	
	return 0;
}
