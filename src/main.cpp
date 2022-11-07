#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

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

    if (!command_line) {
        QApplication app(argc, argv);
        QWidget *w = new QWidget();

        QHBoxLayout *hUserLayout = new QHBoxLayout;
        QLabel *userLabel = new QLabel;
        QLineEdit *userLineEdit = new QLineEdit;
        userLabel->setBuddy(userLineEdit);
        userLabel->setText("Username");
        hUserLayout->addWidget(userLabel);
        hUserLayout->addWidget(userLineEdit);

        QHBoxLayout *hPasswordLayout = new QHBoxLayout;
        QLabel *passwordLabel = new QLabel;
        QLineEdit *passwordLineEdit = new QLineEdit;
        passwordLabel->setBuddy(passwordLineEdit);
        passwordLabel->setText("Password ");
        hPasswordLayout->addWidget(passwordLabel);
        hPasswordLayout->addWidget(passwordLineEdit);

        QHBoxLayout *hButtonsLayout = new QHBoxLayout;
        QPushButton *bLogin = new QPushButton("Login");
        QPushButton *bQuit = new QPushButton("Quit");
        //bLogin->setBuddy(bQuit);
        hButtonsLayout->addWidget(bLogin);
        hButtonsLayout->addWidget(bQuit);

        QLabel *imLabel = new QLabel("Inventory Manager");

        QVBoxLayout *vLoginLayout = new QVBoxLayout;
        vLoginLayout->addWidget(imLabel);
        vLoginLayout->addLayout(hUserLayout);
        vLoginLayout->addLayout(hPasswordLayout);
        vLoginLayout->addLayout(hButtonsLayout);


        w->setLayout(vLoginLayout);
        w->show();

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
