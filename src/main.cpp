#include <iostream>

#include "InventoryManager.hpp"

/* Entry point for InventoryManager */
int main(int argc, char** argv) {
    std::string arg, csv_file;
    bool command_line = false;

    if (argc == 3) {
        arg = argv[1];
        csv_file = argv[2];
        if (arg == "1") command_line = true;
    } else {
        fprintf(stderr, "Usage: bin/main command_line csv_file\n");
        return -1;
    }

    InventoryManager im(command_line, csv_file);

    /* Wrap program in try/catch in case of uncaught exception, we can print it out here. */
    try {
        im.readCSVFile();
        if (im.userLogin()) {
            while (true) {
                if (im.userInput() == -1) break;
            }
        }
        while (true) {
            if (im.userInput() == -1) break;
        }

        im.fileOutput();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;

        return 1;
    }

    return 0;
}
