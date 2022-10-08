#include <iostream>
#include "InventoryManager.hpp"

int main(int argc, char**argv){

	std::string arg, file;
	bool command_line = false;

	if (argc == 3) {
		arg = argv[1];
		if (arg == "1") command_line = true;
		file = argv[2];
	} else {
		fprintf(stderr, "Usage: bin/main command_line file_name\n");
		return -1;
	}

	InventoryManager im(command_line, file);
	
	while (true) {
		if(im.userInput() == -1) break;
	}

	im.fileOutput();
	return 0;
}
