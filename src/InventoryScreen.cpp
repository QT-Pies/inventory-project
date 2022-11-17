#include "InventoryScreen.hpp"

InventoryScreen::InventoryScreen(QWidget *parent) :
    QWidget(parent)
{
    w = new QWidget(parent);
}

InventoryScreen::~InventoryScreen() {
    delete w;
}

void InventoryScreen::OpenWindow(std::shared_ptr<InventoryManager> i) {
    im = i;
    im->readCSVFile();
    w->setWindowTitle("Inventory Manager-Inventory");
    QLabel *totalItemsLabel = new QLabel("TOTAL ITEMS: " + QString::number(im->active_inventory->inv_by_id.size()));

    QListWidget *inventoryList = new QListWidget(this);
    QListWidgetItem *item;
    int j = 0;
    for (auto id_it = im->active_inventory->inv_by_id.begin(); id_it != im->active_inventory->inv_by_id.end(); id_it++) {
        j++;
        item = new QListWidgetItem;
        item->setText(QString::number(id_it->first) + ": " + QString::fromStdString(id_it->second->name));
        inventoryList->addItem(item);
    }

    QPushButton *bQuit = new QPushButton("Quit");
    connect(bQuit, &QPushButton::clicked, this, &InventoryScreen::QuitApp);

    QVBoxLayout *addUserLayout = new QVBoxLayout;

    QPushButton *bAddUser = new QPushButton("Create User");
    connect(bAddUser, &QPushButton::clicked, this, &InventoryScreen::AddUser);

    QHBoxLayout *hUserLayout = new QHBoxLayout;
    QLabel *userLabel = new QLabel;
    userLineEdit = new QLineEdit;
    userLabel->setBuddy(userLineEdit);
    userLabel->setText("Username");
    hUserLayout->addWidget(userLabel);
    hUserLayout->addWidget(userLineEdit);

    QHBoxLayout *hPasswordLayout = new QHBoxLayout;
    QLabel *passwordLabel = new QLabel;
    passwordLineEdit = new QLineEdit;
    passwordLabel->setBuddy(passwordLineEdit);
    passwordLabel->setText("Password ");
    hPasswordLayout->addWidget(passwordLabel);
    hPasswordLayout->addWidget(passwordLineEdit);

    QHBoxLayout *hAccountLayout = new QHBoxLayout;
    ownerButton = new QRadioButton("Owner",this);
    managerButton = new QRadioButton("Manager",this);
    employeeButton = new QRadioButton("Employee",this);
    hAccountLayout->addWidget(ownerButton);
    hAccountLayout->addWidget(managerButton);
    hAccountLayout->addWidget(employeeButton);

    addUserLayout->addLayout(hUserLayout);
    addUserLayout->addLayout(hPasswordLayout);
    addUserLayout->addLayout(hAccountLayout);
    addUserLayout->addWidget(bAddUser);


    QVBoxLayout *windowLayout = new QVBoxLayout;
    windowLayout->addWidget(totalItemsLabel);
    //windowLayout->addWidget(inventoryList);
    windowLayout->addWidget(bQuit);
    windowLayout->addLayout(addUserLayout);

    w->setLayout(windowLayout);
    w->show();
}

void InventoryScreen::QuitApp() {
    w->close();
}

void InventoryScreen::AddUser() {
    w->close();
}