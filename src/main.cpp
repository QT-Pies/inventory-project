#include <iostream>
#include <QApplication>


#include "InventoryManager.hpp"
#include "loginscreen.hpp"

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

    if (!command_line) {
        QApplication app(argc, argv);
        // may want to change the first screen to be a welcome screen
        // this would just say the files it will try to read in
        // then the user hits a button to take them to the login screen
        // maybe just have it automatically open the loginscreen
        // either way, both windows should be open and functional
        // but once login in is sucsessful, they will close and the next window will open
        // this will just be a list of the inventory right now
        LoginScreen ls;
        ls.openWindow(csv_file);

        return app.exec();
    }

    InventoryManager im(command_line, csv_file);

    /* Wrap program in try/catch in case of uncaught exception, we can print it out here. */
    try {
        im.readCSVFile();
        im.userLogin();
        while (true) {
            if (im.userInput() == -1) break;
        }

        im.fileOutput();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;

        /* Call fileOutput and exit with error code. */
        im.fileOutput();

        return 1;
    }

    return 0;
}
