#include <iostream>
#include <QApplication>

#include "InventoryManager.hpp"

/* Entry point for InventoryManager */
int main(int argc, char** argv) {
    std::string arg, csv_file;
    bool command_line = false;
    QApplication a(argc, argv);
    // MainWindow w;

    if (argc == 3) {
        arg = argv[1];
        csv_file = argv[2];
        if (arg == "1") command_line = true;
//        else if (arg == "2") {
//            InventoryManager im(command_line, csv_file);
//            w.show();
//            return a.exec();

//        }
    } else {
        fprintf(stderr, "Usage: bin/main command_line csv_file\n");
        return -1;
    }

   // w.show();
    InventoryManager im(command_line, csv_file);
    // im.readCSVFile_GUI();
    return a.exec();
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

    //return a.exec();
    return 0;
}
