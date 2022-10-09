#include <iostream>
#include "InventoryManager.hpp"

int main(int argc, char**argv){

	std::string arg, csv_file;
	bool command_line = false;

	if (argc == 2) {
		arg = argv[1];
		csv_file = argv[2];
		if (arg == "1") command_line = true;
	} else {
		fprintf(stderr, "Usage: bin/main command_line csv_file\n");
		return -1;
	}

	InventoryManager im(command_line);
	im.readCSVFile(csv_file);
	
	while (true) {
		if(im.userInput() == -1) return -1;
	}

	im.fileOutput();
	return 0;
}
