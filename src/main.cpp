#include <iostream>
#include "InventoryManager.hpp"

int main(int argc, char**argv){

	std::string arg;
	bool command_line = false;

	if (argc == 2) {
		arg = argv[1];
		if (arg == "1") command_line = true;
	} else {
		fprintf(stderr, "Usage: bin/main command_line\n");
		return -1;
	}

	InventoryManager im(command_line);
	
	while (true) {
		if(im.userInput() == -1) return -1;
	}
	return 0;
}
