#include "InventoryManager.hpp"

InventoryManager::InventoryManager(const bool cli, const std::string file) {
    command_line = cli;
    file_name = file;
    sale_list->loadSales(file);
    sales_comp->setup(sale_list);

    inv_header = {"Name", "ID", "Category", "Sub-Category", "Location", "Quantity", "Backorder", "Sale Price", "Tax", "Total Price", "Buy Cost", "Profit", "Expiration Date"};
    item_fields = {"Name", "ID", "Category", "Sub_Category", "Location", "Quantity", "Backorder", "Sale_Price", "Tax", "Total Price", "Buy_Cost", "Profit", "Expiration_Date"};
    inv_update_debounce = false;

}

InventoryManager::~InventoryManager() {
    fileOutput();
    login->outputCSV();
}

int InventoryManager::userInput() {
    std::string argument, arg;
    std::string name, category, sub_category, expiration, value, location;
    std::string id, backorder, quantity, buyer, seller, date;
    std::string sale_price, buy_price, tax;
    bool valid_transaction;
    std::shared_ptr<Item> new_item;
    int x;

    if (command_line == false) {
        Logger::logError("Command line is set to false.  Exiting userInput().");
        return -1;
    }

    std::cout << "\n(A)dd, (R)emove, (U)pdate, (S)ale, (C)hange Permissions, (CS)Compare Sales, (SS)Suggest Sale, "
                 "(P)rint, (L)ogout, or (Q)uit: ";
    std::cin >> argument;
    lowerCaseString(argument);

    /* switch on argument specified from user and then prompt them accordingly for
     * further input */
    if (argument == "a" || argument == "add") {
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        if (current_user->permission < 3) {
            Logger::logWarn("User %s does not have the required permissions to add an Item.",
                            current_user->name.c_str());
            return 0;
        }

        std::cout << "Enter item name: ";
        std::cin >> name;
        std::cout << "Enter item category (Perishable or NonPerishable): ";
        std::cin >> category;
        std::cout << "Enter item sub-category: ";
        std::cin >> sub_category;
        std::cout << "Enter item location: ";
        std::cin >> location;
        std::cout << "Enter item quantity: ";
        std::cin >> quantity;
        std::cout << "Enter backorder (set to zero unless there is negative stock): ";
        std::cin >> backorder;
        std::cout << "Enter item id: ";
        std::cin >> id;
        std::cout << "Enter sale price: (format xx.xx) $";
        std::cin >> sale_price;
        std::cout << "Enter purchase cost: (format xx.xx) $";
        std::cin >> buy_price;
        std::cout << "Enter item tax as a decimal value: ";
        std::cin >> tax;
        std::cout << "Enter expiration date (format xx/xx/xxxx) or -1 for NonPerishable: ";
        std::cin >> expiration;

        lowerCaseString(category);
        try {
            if (category == "perishable") {
                new_item = std::make_shared<PerishableItem>(name, "Perishable", sub_category, location, quantity,
                                                            backorder, id, sale_price, buy_price, tax, expiration);
            } else if (category == "nonperishable") {
                new_item = std::make_shared<NonPerishableItem>(name, "NonPerishable", sub_category, location, quantity,
                                                               backorder, id, sale_price, buy_price, tax);
            } else {
                throw std::runtime_error("Invalid category.");
                return 0;
            }
        } catch (std::exception& e) {
            /* Catch exception, print out its message, but continue to run as normal. */
            Logger::logError(e.what());
            Logger::logWarn("Item %s has not been added to the inventory. Please correct the input and try again.",
                            name.c_str());
            return 0;
        }

        if (active_inventory->addItem(new_item) != -1) {
            std::cout << "Added " << name << " of type " << category << std::endl;
            Logger::logTrace("User %s added Item '%s'.", current_user->name.c_str(), name.c_str());
        }
    } else if (argument == "r" || argument == "remove") {
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        if (current_user->permission < 3) {
            Logger::logWarn("User %s does not have the required permissions to remove an Item.",
                            current_user->name.c_str());
            return 0;
        }

        std::cout << "Name: ";
        std::cin >> name;

        if (active_inventory->removeItem(name) != -1) {
            std::cout << "Removed " << name << std::endl;
            Logger::logTrace("User %s removed Item '%s'.", current_user->name.c_str(), name.c_str());
        }
    } else if (argument == "u" || argument == "update") {
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        if (current_user->permission < 3) {
            Logger::logWarn("User %s does not have the required permissions to update an Item.",
                            current_user->name.c_str());
            return 0;
        }

        std::cout << "Enter name of item to update: ";
        std::cin >> name;
        std::cout << "Enter field to update (e.g. name, id, tax, etc): ";
        std::cin >> category;
        std::cout << "Enter new value for " << category << ": ";
        std::cin >> value;

        if (active_inventory->updateItem(name, category, value) != -1) {
            std::cout << "Updated " << category << " of " << name << " to " << value << std::endl;
            Logger::logTrace("User %s updated %s of Item '%s' to %s.", current_user->name.c_str(), category.c_str(),
                             name.c_str(), value.c_str());
        }

    } else if (argument == "c" || argument == "change") {
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        std::cout << "Account name: ";
        std::cin >> name;
        std::cout << "New account type: ";
        std::cin >> category;

        if (updatePermission(name, category)) {
            Logger::logTrace("User %s updated account of '%s' to '%s'.", current_user->name.c_str(), name.c_str(),
                             category.c_str());
        }
    } else if (argument == "cs" || argument == "compare") {
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        std::cout << "\nPlease select a range to compare against.\n";
        std::cout << "(Input your choice as the exact string below as you see it.)\n";
        std::cout << "All_By_Year | All_By_Month | X_Years | Last_Month | Last_7_days | Yesterday | Full\n";
        std::cin >> category;

        if (category == "Full") {
            sales_comp->printAllComparisons();
        } else if (category == "All_By_Year") {
            sales_comp->printComparison("ByYear", 0);
        } else if (category == "All_By_Month") {
            sales_comp->printComparison("ByMonth", 0);
        } else if (category == "X_Years") {
            std::cout << "Number of years to compare : ";
            std::cin >> x;
            while (x <= 0) {
                std::cout << "Invalid number of years. Try again.\n";
                std::cout << "Number of years to compare : ";
                std::cin >> x;
            }
            sales_comp->printComparison("LastXYears", x);
        } else if (category == "Last_Month") {
            sales_comp->printComparison("LastMonth", 0);
        } else if (category == "Last_7_days") {
            sales_comp->printComparison("Last7Days", 0);
        } else if (category == "Yesterday") {
            sales_comp->printComparison("Yesterday", 0);
        }
    } else if (argument == "ss" || argument == "suggest") {
        std::cout << std::endl;
        sales_comp->suggestSale();

    } else if (argument == "p" || argument == "print") {
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        std::cout << "\nPlease select a category to print or an item name.\n";
        std::cout << "All | Perishable | NonPerishable | Location | Item Name : ";
        std::cin >> category;
        if (category == "Location") {
            std::cout << "Location: ";
            std::cin >> location;
            active_inventory->printItems(category, location);
        } else {
            active_inventory->printItems("", category);
        }
        Logger::logTrace("User %s viewed the inventory.", current_user->name.c_str());
    } else if (argument == "s" || argument == "sales") {
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        valid_transaction = false;

        std::cout << "\nCustomer name: ";
        std::cin >> buyer;
        std::cout << "Seller name (you): ";
        std::cin >> seller;

        do {
            unsigned long tmp_quantity;
            sale_list->userTransaction(sale_list->curr_sale_id, buyer, seller);

            std::cout << "\nItem Name: ";
            std::cin >> name;
 
        while (1) {
            try {
                std::cout << "Quantity Sold: ";
                std::cin >> quantity;
                tmp_quantity = toUnsignedLong(quantity);
                if (tmp_quantity == 0) {
                    throw std::invalid_argument("Quantity can't be zero.");
                }
                break;
            } catch (std::exception& e) {
                Logger::logDebug(e.what());
                std::cout << "Invalid quantity. Try again.\n";
            }
        }
           
            auto item_ptr = active_inventory->searchByName(name);

            if (item_ptr != NULL) {
                sale_list->transaction_by_order[sale_list->curr_transaction]->addSale(
                    sale_list->curr_sale_id, item_ptr->id, tmp_quantity, item_ptr->sale_price);
                valid_transaction = true;
            } else valid_transaction = false;

            /* if no valid sales are added to the transaction, then it is deleted */
            if (valid_transaction == false) {
                Logger::logError("Invalid transaction -- no valid sales were input.\n");
                sale_list->transaction_by_order.pop_back();
                sale_list->curr_transaction--;
            } else {
                std::cout << "\n" << quantity << " " << name << "(s) sold.\n"; 
                std::cout << "End of transaction. Thank you!\n\n";
                sale_list->curr_sale_id++;
                makeTransaction();
                Logger::logTrace("User %s entered a transaction.", current_user->name.c_str());
            }
            std::cout << "Would customer \"" << buyer << "\" like to make another transaction? (Y/N): ";
            std::cin >> arg;
            lowerCaseString(arg);

            while (arg != "y" && arg != "n" ) {
                std::cout << "Would customer \"" << buyer << "\" like to make another transaction? (Y/N): ";
                std::cin >> arg;
                lowerCaseString(arg);
            }
        } while (arg != "n");

        std::cout << "Exiting Sales. Thank you for your business!\n";

    } else if (argument == "l" || argument == "logout") {
        Logger::logTrace("User %s logged out.", current_user->name.c_str());
        current_user = NULL;

        return userLogin() ? 0 : -1;

    } else if (argument == "q" || argument == "quit") {
        printf("Exiting InventoryManager.\n");
        Logger::logTrace("User %s exited the program.", current_user->name.c_str());
        login->outputCSV();
        return -1;
    } else {
        std::cout
            << "Usage: <(A)dd | (R)emove | (U)pdate | (S)ale | (C)hange Permissions | (P)rint | (L)ogout | (Q)uit>"
            << std::endl;
    }

    std::cin.clear();
    std::cin.ignore(10000, '\n');

    return 0;
}

void InventoryManager::guiLogin() {
    view_gc.clear();

    auto login_view = std::make_shared<QWidget>(window.get());
    login_view->setFixedSize(960, 540);
    view = login_view;

    auto logo = new QLabel(login_view.get());
    QPixmap logo_image("./images/logo.png");
    logo->setPixmap(logo_image.scaled(256,256,Qt::KeepAspectRatio));
    logo->move(352,0);
    gc.push_back(logo);

    auto user_label = new QLabel(login_view.get());
    user_label->setText("Username:");
    user_label->move(352,260);
    username_line = new QLineEdit(login_view.get());
    username_line->move(440,256);
    gc.push_back(user_label);
    gc.push_back(username_line);

    auto password_label = new QLabel(login_view.get());
    password_label->setText("Password:");
    password_label->move(352,300);
    password_line = new QLineEdit(login_view.get());
    password_line->move(440,296);
    password_line->setEchoMode(QLineEdit::Password);
    gc.push_back(password_label);
    gc.push_back(password_line);


    auto login_button = new QPushButton(login_view.get());
    login_button->setText("Login");
    login_button->setFixedSize(256,64);
    login_button->move(352, 340);
    login_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    gc.push_back(login_button);

    auto quit_button = new QPushButton(login_view.get());
    quit_button->setText("Quit");
    quit_button->setFixedSize(256,64);
    quit_button->move(352, 400);
    quit_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    gc.push_back(quit_button);

    QObject::connect(login_button, &QPushButton::clicked, [&]() {
        //std::cout << "Hello, I am a QPushButton and I have been pressed." << std::endl;

        QString un = username_line->text();
        QString pas = password_line->text();

        auto user = login->verifyUser(un.toStdString(), pas.toStdString());

        if (user != nullptr) {
            /* Switch to main program view */
            current_user = user;
            view->hide();
            mainWindow();
        }
        else {
            /* display error popup if invalid*/
            QMessageBox box;
            box.setWindowTitle("Login");
            box.setText("Username and/or password is incorrect");
            box.exec();
        }
    });

    QObject::connect(quit_button, &QPushButton::clicked, [&]() {
        window->close();
        return;
    });

    login_view->show();
}

void InventoryManager::guiUser() {
    if (sub_view != nullptr) sub_view->hide();

    if (user_screen != nullptr) {
        sub_view = user_screen;
        sub_view->show();
        return;
    }

    user_screen = std::make_shared<QWidget>(view.get());
    user_screen->setFixedSize(880, 540);
    user_screen->move(80,0);

    auto user_label = new QLabel(user_screen.get());
    user_label->setText("Username:");
    user_label->move(352,160);
    username_line = new QLineEdit(user_screen.get());
    username_line->move(440,156);
    user_label->show();
    username_line->show();
    gc.push_back(user_label);
    gc.push_back(username_line);

    auto password_label = new QLabel(user_screen.get());
    password_label->setText("Password:");
    password_label->move(352,200);
    password_line = new QLineEdit(user_screen.get());
    password_line->move(440,196);
    password_label->show();
    password_line->show();
    // password_line->setEchoMode(QLineEdit::Password);
    gc.push_back(password_label);
    gc.push_back(password_line);

    ownerButton = new QRadioButton("Owner",user_screen.get());
    managerButton = new QRadioButton("Manager",user_screen.get());
    employeeButton = new QRadioButton("Employee",user_screen.get());
    ownerButton->move(325,300);
    managerButton->move(425,300);
    employeeButton->move(525,300);
    ownerButton->show();
    managerButton->show();
    employeeButton->show();

    auto create_button = new QPushButton(user_screen.get());
    create_button->setText("Create User");
    create_button->setFixedSize(256,64);
    create_button->move(352, 340);
    create_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    create_button->show();
    gc.push_back(create_button);

    auto update_button = new QPushButton(user_screen.get());
    update_button->setText("Update User");
    update_button->setFixedSize(256,64);
    update_button->move(352, 410);
    update_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    update_button->show();
    gc.push_back(update_button);

    auto logout_button = new QPushButton(user_screen.get());
    logout_button->setText("Logout");
    logout_button->setFixedSize(256,64);
    logout_button->move(352, 480);
    logout_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    logout_button->show();
    gc.push_back(logout_button);

    QObject::connect(create_button, &QPushButton::clicked, [&]() {
        QString un = username_line->text();
        QString pas = password_line->text();
        QString acc = "";
        //std::string acc_string;

        QMessageBox box;

        if(ownerButton->isChecked()) {
            acc = "owner";
        }
        else if(managerButton->isChecked()) {
            acc = "manager";
        }
        else if(employeeButton->isChecked()) {
            acc = "employee";
        }

         if(un == "") {
            // QMessageBox::warning(w,"Didn't create New User", "Username is blank.");
            box.setWindowTitle("Create User");
            box.setText("Username is blank.");
            box.exec();
            return;
        }
        else if(pas == "") {
            //QMessageBox::warning(w,"Didn't create New User", "Password is blank.");
            box.setWindowTitle("Create User");
            box.setText("Password is blank.");
            box.exec();
            return;
        }
        else if(acc == "") {
            // QMessageBox::warning(w,"Didn't create New User", "Plesase select an account type.");
            box.setWindowTitle("Create User");
            box.setText("Please select an account type.");
            box.exec();
            return;
        }

         if(current_user->permission == 1) {
            //QMessageBox::warning(w,"Didn't create New User", "Employees cannot create accounts. Please have a manager or owner create the account.");
            box.setWindowTitle("Create User");
            box.setText("Employees cannot create accounts. Please have a manager or owner create the account.");
            box.exec();
            return;
        }
        else if(current_user->permission == 3 && (acc == "owner" || acc == "manager")) {
            //QMessageBox::warning(w,"Didn't create New User", "Managers can only create employee accounts. Please have an owner create the account.");
            box.setWindowTitle("Create User");
            box.setText("Managers can only create employee accounts. Please have an owner create the account.");
            box.exec();
            return;
        }
        if(login->createUser(un.toStdString(), pas.toStdString(), acc.toStdString())) {
        //QMessageBox::information(w, "Create User", "Created user Succsessfuly");
            box.setWindowTitle("Create User");
            box.setText("Created user succsessfuly");
            box.exec();
        }
        else {
            //QMessageBox::warning(w,"Didn't create New User", "The User was unable to be created. Allready Exists");
            box.setWindowTitle("Create User");
            box.setText("User was unable to be created. User allready exists.");
            box.exec();
        }
    });

    QObject::connect(update_button, &QPushButton::clicked, [&]() {
        QString un = username_line->text();
        QString acc = "";
        QMessageBox box;

        if(current_user->permission != 5) {
            box.setWindowTitle("Update User");
            box.setText("Only Owners can update users.");
            box.exec();
            return;
        }

        if(ownerButton->isChecked()) {
            acc = "owner";
        }
        else if(managerButton->isChecked()) {
            acc = "manager";
        }
        else if(employeeButton->isChecked()) {
            acc = "employee";
        }

        if(un == "") {
            // QMessageBox::warning(w,"Didn't create New User", "Username is blank.");
            box.setWindowTitle("Update User");
            box.setText("Username is blank.");
            box.exec();
            return;
        }
        else if(acc == "") {
            // QMessageBox::warning(w,"Didn't create New User", "Plesase select an account type.");
            box.setWindowTitle("Update User");
            box.setText("Please select an account type.");
            box.exec();
            return;
        }

        if(updatePermission(un.toStdString(), acc.toStdString())) {
            box.setWindowTitle("Update User");
            box.setText("Updated user succsessfuly.");
            box.exec();
        }
        else {
            box.setWindowTitle("Update User");
            box.setText("Unable to update user.");
            box.exec();
        }
    });

    QObject::connect(logout_button, &QPushButton::clicked, [&]() {
        window->close();
        return;
    });
    user_screen->show();
}

void InventoryManager::guiSaleComparison() {
    if (sub_view != nullptr) sub_view->hide();

    if (sc_screen != nullptr) {
        sub_view = sc_screen;
        sub_view->show();
        return;
    }

    sc_screen = std::make_shared<QWidget>(view.get());
    sc_screen->setFixedSize(880, 540);
    sc_screen->move(80,0);

    // lables that will be changed based on the pressed button
    ya_label = new QLabel(sc_screen.get());
    ys_label = new QLabel(sc_screen.get());
    yg_label = new QLabel(sc_screen.get());
    ma_label = new QLabel(sc_screen.get());
    ms_label = new QLabel(sc_screen.get());
    mg_label = new QLabel(sc_screen.get());
    lmc_label = new QLabel(sc_screen.get());
    l7dc_label = new QLabel(sc_screen.get());
    yc_label = new QLabel(sc_screen.get());
    xy_label = new QLabel(sc_screen.get());

    ya_label->setText("TEST");
    ys_label->setText("TEST");
    yg_label->setText("TEST");
    ma_label->setText("TEST");
    ms_label->setText("TEST");
    mg_label->setText("TEST");
    lmc_label->setText("TEST");
    l7dc_label->setText("TEST");
    yc_label->setText("TEST");
    xy_label->setText("TEST");

    ya_label->move(400,20);
    ys_label->move(400,40);
    yg_label->move(400,60);
    ma_label->move(400,80);
    ms_label->move(400,100);
    mg_label->move(400,120);
    lmc_label->move(400,140);
    l7dc_label->move(440,160);
    yc_label->move(400,180);
    xy_label->move(80,200);

    ya_label->hide();
    ys_label->hide();
    yg_label->hide();
    ma_label->hide();
    ms_label->hide();
    mg_label->hide();
    lmc_label->hide();
    l7dc_label->hide();
    yc_label->hide();
    xy_label->hide();

    auto year_average_label = new QLabel(sc_screen.get());
    year_average_label->setText("Average Sales Per Year:");
    year_average_label->move(80, 20);
    year_average_label->show();
    gc.push_back(year_average_label);

    auto year_sales_label = new QLabel(sc_screen.get());
    year_sales_label->setText("Sales So Far This Year:");
    year_sales_label->move(80, 40);
    year_sales_label->show();
    gc.push_back(year_sales_label);

    auto year_gain_label = new QLabel(sc_screen.get());
    year_gain_label->setText("Gain This Year vs Average (%):");
    year_gain_label->move(80, 60);
    year_gain_label->show();
    gc.push_back(year_gain_label);

    auto month_average_label = new QLabel(sc_screen.get());
    month_average_label->setText("Average Sales Per Month:");
    month_average_label->move(80, 80);
    month_average_label->show();
    gc.push_back(month_average_label);

    auto month_sales_label = new QLabel(sc_screen.get());
    month_sales_label->setText("Sales So Far This Month:");
    month_sales_label->move(80, 100);
    month_sales_label->show();
    gc.push_back(month_sales_label);

    auto month_gain_label = new QLabel(sc_screen.get());
    month_gain_label->setText("Gain This Month vs Average (%):");
    month_gain_label->move(80, 120);
    month_gain_label->show();
    gc.push_back(month_gain_label);

    auto last_month_comparison_label = new QLabel(sc_screen.get());
    last_month_comparison_label->setText("Sales This Month Compared To Last Month (%):");
    last_month_comparison_label->move(80, 140);
    last_month_comparison_label->show();
    gc.push_back(last_month_comparison_label);

    auto last_7_days_comparison_label = new QLabel(sc_screen.get());
    last_7_days_comparison_label->setText("*Sales Over The Last 7 days Compared To Today (%):");
    last_7_days_comparison_label->move(80, 160);
    last_7_days_comparison_label->show();
    gc.push_back(last_7_days_comparison_label);

    auto yesterday_comparison_label = new QLabel(sc_screen.get());
    yesterday_comparison_label->setText("*Sales Yesterday Compared To Today (%):");
    yesterday_comparison_label->move(80, 180);
    yesterday_comparison_label->show();
    gc.push_back(yesterday_comparison_label);

    auto x_years_label = new QLabel(sc_screen.get());
    x_years_label->setText("Sales So Far This Year Compared To The Average Over The Past X Years:");
    x_years_label->move(80, 200);
    x_years_label->show();
    gc.push_back(x_years_label);

    auto comparison_warning_label = new QLabel(sc_screen.get());
    comparison_warning_label->setText("* These Numbers Will Be Lower Earlier In The Day And Only Show Accurate Comparisons At The End Of the Day.");
    comparison_warning_label->move(80, 400);
    comparison_warning_label->show();
    gc.push_back(comparison_warning_label);

    auto all_by_year_button = new QPushButton(sc_screen.get());
    all_by_year_button->setText("All By Year");
    all_by_year_button->setFixedSize(200,60);
    all_by_year_button->move(480, 480);
    all_by_year_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    all_by_year_button->show();
    gc.push_back(all_by_year_button);

    auto all_by_month_button = new QPushButton(sc_screen.get());
    all_by_month_button->setText("All By Month");
    all_by_month_button->setFixedSize(200,60);
    all_by_month_button->move(680, 480);
    all_by_month_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    all_by_month_button->show();
    gc.push_back(all_by_month_button);

    auto years_label = new QLabel(sc_screen.get());
    years_label->setText("X:");
    years_label->move(80,500);
    years_label->show();
    gc.push_back(years_label);

    years_line = new QLineEdit(sc_screen.get());
    years_line->move(95,500);
    years_line->show();
    gc.push_back(years_line);

    auto x_years_button = new QPushButton(sc_screen.get());
    x_years_button->setText("X Years");
    x_years_button->setFixedSize(200,60);
    x_years_button->move(280, 480);
    x_years_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    x_years_button->show();
    gc.push_back(x_years_button);

    auto last_month_button = new QPushButton(sc_screen.get());
    last_month_button->setText("Last Month");
    last_month_button->setFixedSize(200,60);
    last_month_button->move(280, 420);
    last_month_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    last_month_button->show();
    gc.push_back(last_month_button);

    auto last_7_days_button = new QPushButton(sc_screen.get());
    last_7_days_button->setText("Last 7 Days");
    last_7_days_button->setFixedSize(200,60);
    last_7_days_button->move(480, 420);
    last_7_days_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    last_7_days_button->show();
    gc.push_back(last_7_days_button);

    auto yesterday_button = new QPushButton(sc_screen.get());
    yesterday_button->setText("Yesterday");
    yesterday_button->setFixedSize(200,60);
    yesterday_button->move(680, 420);
    yesterday_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    yesterday_button->show();
    gc.push_back(yesterday_button);

    auto full_button = new QPushButton(sc_screen.get());
    full_button->setText("Full");
    full_button->setFixedSize(200,60);
    full_button->move(80, 420);
    full_button->setStyleSheet("background-color: rgba(178, 255, 158, 255); color: #000000;");
    full_button->show();
    gc.push_back(full_button);
    // ya_label->
    // ys_label->
    // yg_label->
    // ma_label->
    // ms_label->
    // mg_label->
    // lmc_label->
    // l7dc_label->
    // yc_label->
    // xy_label->

    // ya_label->hide();
    // ys_label->hide();
    // yg_label->hide();
    // ma_label->hide();
    // ms_label->hide();
    // mg_label->hide();
    // lmc_label->hide();
    // l7dc_label->hide();
    // yc_label->hide();
    // xy_label->hide();

QObject::connect(full_button, &QToolButton::clicked, [&]() {
    std::cout << "I am the Full button and I have been clicked." << std::endl;
    // ya_label->
    // ys_label->
    // yg_label->
    // ma_label->
    // ms_label->
    // mg_label->
    // lmc_label->
    // l7dc_label->
    yc_label->show();
    // xy_label->
        
});

QObject::connect(yesterday_button, &QToolButton::clicked, [&]() {
    std::cout << "I am the Yesterday button and I have been clicked." << std::endl;
    ya_label->hide();
    ys_label->hide();
    yg_label->hide();
    ma_label->hide();
    ms_label->hide();
    mg_label->hide();
    lmc_label->hide();
    l7dc_label->hide();
    // yc_label->hide();
    xy_label->hide();
    // yc_label->setText("TEST");
    yc_label->show();
    //hideAllViews();
    //sc_screen->show();
        
});

    sc_screen->show();
}

void InventoryManager::insertItemIntoTable(std::shared_ptr<Item> item, int row) {

    std::cout << "line 328" << std::endl;

    auto name = QString::fromStdString(item->name);
    auto id = QString::number(item->id);
    auto category = QString::fromStdString(item->category);
    auto subcategory = QString::fromStdString(item->sub_category);
    auto location = QString::fromStdString(item->location);
    auto quantity = QString::number(item->quantity);
    auto backorder = QString::number(item->backorder);
    auto sale_price = QString::number(item->sale_price);
    auto tax = QString::number(item->tax);
    auto total_price = QString::number(item->total_price);
    auto buy_cost = QString::number(item->buy_cost);
    auto profit = QString::number(item->profit);
    QString expiration_date;

    std::cout << "line 344" << std::endl;

    /* Special expiration date logic. */
    if (item->category == "Perishable") {
        PerishableItem *tmp = (PerishableItem*) item.get();
        expiration_date = QString::fromStdString(tmp->expiration_date.string_date);
    } else expiration_date = "-1";

    /* Create QTableWidgetItem for each field */
    auto name_entry = new QTableWidgetItem(name, 0);
    auto id_entry = new QTableWidgetItem(id, 0);
    auto cat_entry = new QTableWidgetItem(category, 0);
    auto sub_entry = new QTableWidgetItem(subcategory, 0);
    auto location_entry = new QTableWidgetItem(location, 0);
    auto quantity_entry = new QTableWidgetItem(quantity, 0);
    auto backorder_entry = new QTableWidgetItem(backorder, 0);
    auto sale_entry = new QTableWidgetItem(sale_price, 0);
    auto tax_entry = new QTableWidgetItem(tax, 0);
    auto total_entry = new QTableWidgetItem(total_price, 0);
    auto buy_entry = new QTableWidgetItem(buy_cost, 0);
    auto profit_entry = new QTableWidgetItem(profit, 0);
    auto exp_entry = new QTableWidgetItem(expiration_date, 0);

    std::cout << "line 367" << std::endl;
    std::cout << "rowCount == " << table->rowCount() << std::endl;

    if (table == nullptr) {
        std::cout << "Table has become null somehow." << std::endl;
    }

    /* Insert each item into table */
    table->setItem(row, 0, name_entry);
    table->setItem(row, 1, id_entry);
    table->setItem(row, 2, cat_entry);
    table->setItem(row, 3, sub_entry);
    table->setItem(row, 4, location_entry);
    table->setItem(row, 5, quantity_entry);
    table->setItem(row, 6, backorder_entry);
    table->setItem(row, 7, sale_entry);
    table->setItem(row, 8, tax_entry);
    table->setItem(row, 9, total_entry);
    table->setItem(row, 10, buy_entry);
    table->setItem(row, 11, profit_entry);
    table->setItem(row, 12, exp_entry);

    std::cout << "line 384" << std::endl;
}

void InventoryManager::helpScreen() {
    if (sub_view != nullptr) sub_view->hide();

    if (help_screen != nullptr) {
        sub_view = help_screen;
        sub_view->show();
        return;
    }

    help_screen = std::make_shared<QWidget>(view.get());
    help_screen->setFixedSize(880, 540);
    help_screen->move(80,0);


    auto welcome_text = new QLabel(help_screen.get());
    welcome_text->setText("Welcome to Inventory Manager!");
    welcome_text->setFixedSize(480, 270);
    welcome_text->move(300, 135);
    welcome_text->show();

    help_screen->show();
    return;
}

void InventoryManager::hideAllViews() {
    if (inv_screen != nullptr) inv_screen->hide();
    if (help_screen != nullptr) help_screen->hide();
    if (user_screen != nullptr) user_screen->hide();
    if (sc_screen != nullptr) sc_screen->hide();
}

void InventoryManager::redrawTable() {
    table->setRowCount(0);
    auto item_count = static_cast<int>(active_inventory->inv_by_id.size());
    table->setRowCount(item_count);

    int row = 0;
    for (auto it = active_inventory->inv_by_id.begin(); it != active_inventory->inv_by_id.end(); ++it, ++row) {
        std::cout << "Calling insertItem with item, row number = " << row << std::endl;
        std::cout << "Current rowCount = " << table->rowCount() << std::endl;
        insertItemIntoTable(it->second, row);
    }
}

int InventoryManager::displayInventory() {
    auto item_count = static_cast<int>(active_inventory->inv_by_id.size());
    int row;

    if (sub_view == inv_screen) {
        std::cout << "Already on inventory screen" << std::endl;
    } else if (sub_view == help_screen) {
        std::cout << "On help screen" << std::endl;
    }

    if (sub_view != nullptr) sub_view->hide();
    else std::cout << "No active sub view" << std::endl;
     
    if (inv_screen != nullptr) {
        sub_view = inv_screen;
        inv_screen->show();
        return 0;
    }

    inv_screen = std::make_shared<QWidget>(view.get());
    inv_screen->setFixedSize(880, 540);
    inv_screen->move(80, 0);

    table = std::make_shared<QTableWidget>(item_count + 1, static_cast<int>(inv_header.size()), inv_screen.get());
    table->setHorizontalHeaderLabels(inv_header);
    table->setFixedSize(880, 500);
    table->move(0, 0);

    sub_view = inv_screen;

    auto bar = new QToolBar(inv_screen.get());
    bar->setFixedSize(880, 40);
    bar->move(0, 500);
    bar->show();

    /* Create Add action */
    auto add_action = new QAction(bar);
    add_action->setIcon(QIcon("./images/add.png"));
    bar->addAction(add_action);

    auto remove_action = new QAction(bar);
    remove_action->setIcon(QIcon("./images/remove.png"));
    bar->addAction(remove_action);

    redrawTable();

    /* Field was changed; attempt to update it. */
    QObject::connect(table.get(), &QTableWidget::itemChanged, [&](QTableWidgetItem* item) {
        auto item_name = table->item(item->row(), 0)->text().toStdString();
        auto cat = item_fields.at(item->column()).toStdString();
        auto val = item->text().toStdString();

        /* Skip updating anything if we were called from a manual setText() */
        if (inv_update_debounce) {
            inv_update_debounce = false;
            return;
        }

        /* So, ActiveInventory::updateItem() takes the item name. 
         * Currently, we grab the item name by checking the first column of this row.
         * However, if we're updating the name, we can't use that.\
         * Instead, grab ID, get item with that ID, then get name from that.
        */
        if (item->column() == 0) {
            try {
                auto id = toUnsignedLong(table->item(item->row(), 1)->text().toStdString());
                auto item = active_inventory->searchById(id);

                if (item == nullptr) {
                    throw std::invalid_argument("Failed to find the item.");
                }

                item_name = item->name;
            } catch (std::exception& e) {
                Logger::logWarn(e.what());
                return;
            }
        }

        /* If failed to update, revert the text to the actual current value. */
        if (active_inventory->updateItem(item_name, cat, val)) {       
            auto inv_item = active_inventory->searchByName(item_name);
            Logger::logTrace("Failed to update Item '%s' field '%s' to value '%s'.", item_name.c_str(), cat.c_str(), val.c_str());

            QString q_string;

            if (cat == "Name") {
                q_string = QString::fromStdString(inv_item->name);
            } else if (cat == "ID") {
                q_string = QString::number(inv_item->id);
            } else if (cat == "Category") {
                q_string = QString::fromStdString(inv_item->category);
            } else if (cat == "Sub_Category") {
                q_string = QString::fromStdString(inv_item->sub_category);
            } else if (cat == "Location") {
                q_string = QString::fromStdString(inv_item->location);
            } else if (cat == "Quantity") {
                q_string = QString::number(inv_item->quantity);
            } else if (cat == "Backorder") {
                q_string = QString::number(inv_item->backorder);
            } else if (cat == "Sale_Price") {
                q_string = QString::number(inv_item->sale_price);
            } else if (cat == "Tax") {
                q_string = QString::number(inv_item->tax);
            } else if (cat == "Buy Cost") {
                q_string = QString::number(inv_item->buy_cost);
            } else if (cat == "Profit") {
                q_string = QString::number(inv_item->profit);
            } else if (cat == "Expiration_Date") {
                if (inv_item->category == "NonPerishable") {
                    q_string = "-1";
                } else {
                    auto per_item = (PerishableItem*) inv_item.get();
                    q_string = QString::fromStdString(per_item->expiration_date.string_date);
                }
            }

            inv_update_debounce = true;
            item->setText(q_string);
        }
    });

    QObject::connect(add_action, &QAction::triggered, [&]() {
        auto input = AddDialog::getStrings(view.get());
        auto name = input.at(0).toStdString();
        auto id = input.at(1).toStdString();
        auto category = input.at(2).toStdString();
        auto sub_category = input.at(3).toStdString();
        auto location = input.at(4).toStdString();
        auto quantity = input.at(5).toStdString();
        auto backorder = input.at(6).toStdString();
        auto sale_price = input.at(7).toStdString();
        auto tax = input.at(8).toStdString();
        auto buy_cost = input.at(9).toStdString();
        auto expiration_date = input.at(10).toStdString();
        std::shared_ptr<Item> new_item;

        lowerCaseString(category);
        try {
            if (category == "perishable") {
                new_item = std::make_shared<PerishableItem>(name, "Perishable", sub_category, location, quantity,
                                                            backorder, id, sale_price, buy_cost, tax, expiration_date);
            } else if (category == "nonperishable") {
                new_item = std::make_shared<NonPerishableItem>(name, "NonPerishable", sub_category, location, quantity,
                                                               backorder, id, sale_price, buy_cost, tax);
            } else {
                throw std::runtime_error("Invalid category.");
                return;
            }
        } catch (std::exception& e) {
            /* Catch exception, print out its message, but continue to run as normal. */
            Logger::logError(e.what());
            Logger::logWarn("Item %s has not been added to the inventory. Please correct the input and try again.",
                            name.c_str());
            return;
        }

        if (active_inventory->addItem(new_item) != -1) {
            Logger::logTrace("User %s added Item '%s'.", current_user->name.c_str(), name.c_str());
        }
    });

    QObject::connect(remove_action, &QAction::triggered, [&]() {
        auto name = QInputDialog::getText(view.get(), "Remove Item from Inventory", "Name of Item:", QLineEdit::Normal);

        auto item = active_inventory->searchByName(name.toStdString());

        if (item == nullptr) {
            Logger::logWarn("Could not find item '%s' in the inventory.", name.toStdString().c_str());
        }

        for (row = 1; row < table->rowCount(); ++row) {
            auto row_id = toUnsignedLong(table->item(row, 1)->text().toStdString());

            if (row_id == item->id) {
                table->removeRow(row);
                active_inventory->removeItem(item->name);
                Logger::logTrace("User %s remove Item '%s'.", current_user->name.c_str(), name.toStdString().c_str());
                return;
            }
        }

    });

    table->show();
    inv_screen->show();
    return 0;
}

void InventoryManager::initializeSidePanel() {
    /* Clear out current gc collection */
    view_gc.clear();

    /* Set up side panel buttons */

    /* Inventory Button to switch to inventory view */
    auto inv_button = new QToolButton(view.get());
    inv_button->setIcon(QIcon("./images/inventory-button.png"));
    inv_button->setIconSize(QSize(80, 80));
    inv_button->move(-5,0);
    inv_button->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    inv_button->show();

    /* Help Button to switch to help view */
    auto help_button = new QToolButton(view.get());
    help_button->setIcon(QIcon("./images/about.png"));
    help_button->setIconSize(QSize(80, 80));
    help_button->move(-5, 455);
    help_button->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    help_button->show();

    /* Add User Button to switch to add user view */
    auto user_button = new QToolButton(view.get());
    user_button->setIcon(QIcon("./images/user.png"));
    user_button->setIconSize(QSize(80, 80));
    user_button->move(-5, 365);
    user_button->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    user_button->show();

    /* Add SaleComparison Button to switch to add user view */
    auto sc_button = new QToolButton(view.get());
    sc_button->setIcon(QIcon("./images/salecomparison.png"));
    sc_button->setIconSize(QSize(80, 80));
    sc_button->move(-5, 275);
    sc_button->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    sc_button->show();

    QObject::connect(inv_button, &QToolButton::clicked, [&]() {
        std::cout << "I am the inventory button and I have been clicked." << std::endl;
        hideAllViews();
        displayInventory();
    });

    QObject::connect(help_button, &QToolButton::clicked, [&]() {
        std::cout << "I am the help button and I have been clicked." << std::endl;
        hideAllViews();
        helpScreen();
    });

    QObject::connect(user_button, &QToolButton::clicked, [&]() {
        std::cout << "I am the user button and I have been clicked." << std::endl;
        hideAllViews();
        guiUser();
    });

    QObject::connect(sc_button, &QToolButton::clicked, [&]() {
        std::cout << "I am the sale comparison button and I have been clicked." << std::endl;
        hideAllViews();
        guiSaleComparison();
    });
}

void InventoryManager::mainWindow() {
    auto main_view = std::make_shared<QWidget>(window.get());

    main_view->setFixedSize(960, 540);
    view = main_view;

    initializeSidePanel();

    // Open up inventory view on program login.
    displayInventory();

    main_view->show();
}

int InventoryManager::guiInput(int argc, char** argv) {
    app = std::make_shared<QApplication>(argc, argv);
    window = std::make_shared<QWidget>();

    window->resize(960, 540);
    window->setFixedSize(960, 540);
    window->setWindowTitle(QApplication::translate("InventoryManager", "Inventory Manager"));

    guiLogin();

    window->show();
    app->exec();
    return 0;
}

void InventoryManager::readCSVFile() {
    std::string name, str_id, cat, sub_cat, location, qty, back, sale_price;
    std::string tax, total_price, buy_cost, profit, exp, tmp_line;
    std::shared_ptr<Item> new_item;
    unsigned long lines_read, lines_successful, errors;

    std::ifstream csv_file(file_name);

    if (!csv_file.is_open()) {
        Logger::logError("Failed to open file '%s'.  No inventory will be loaded.", file_name.c_str());
        return;
    }

    /* This skips the first line for you. */
    std::getline(csv_file, tmp_line);

    lines_successful = 0;
    lines_read = 0;
    errors = 0;

    while (csv_file.good()) {
        /*reading in the csv info, converting types*/
        getline(csv_file, name, ',');

        /*exit the loop if we don't read in a new name.*/
        if (!csv_file.good()) break;
        ++lines_read;

        getline(csv_file, str_id, ',');
        getline(csv_file, cat, ',');
        getline(csv_file, sub_cat, ',');
        getline(csv_file, location, ',');
        getline(csv_file, qty, ',');
        getline(csv_file, back, ',');
        getline(csv_file, sale_price, ',');
        getline(csv_file, tax, ',');
        getline(csv_file, total_price, ',');
        getline(csv_file, buy_cost, ',');
        getline(csv_file, profit, ',');
        getline(csv_file, exp, '\n');

        try {
            /* Create the Item to be added. */
            if (cat == "Perishable") {
                new_item = std::make_shared<PerishableItem>(name, cat, sub_cat, location, qty, back, str_id, sale_price,
                                                            buy_cost, tax, exp);
            } else if (cat == "NonPerishable") {
                new_item = std::make_shared<NonPerishableItem>(name, cat, sub_cat, location, qty, back, str_id,
                                                               sale_price, buy_cost, tax);
            } else {
                throw std::runtime_error("Bad category for Item.");
            }
        } catch (std::exception& e) {
            ++errors;
            Logger::logInfo(e.what());
            continue;
        }

        /* Add the item to the active inventory. */
        active_inventory->addItem(new_item);

        /* Test to see if we successfully read in item. */
        auto item_ptr = active_inventory->searchByName(name);

        if (item_ptr == NULL) {
            Logger::logError("Failed to read new Item '%s", name.c_str());
        }

        ++lines_successful;
    }

    if (lines_read != lines_successful) {
        Logger::logError(
            "Attempted to read %lu lines, but only successfully read %lu.  These %lu lines will not be stored into the "
            "inventory and will be lost on program exit.",
            lines_read, lines_successful, lines_read - lines_successful);
    }
}

int InventoryManager::fileOutput() {
    std::ofstream file;
    std::map<std::string, std::shared_ptr<Item>>::iterator mit;

    file.open(file_name);

    if (!file.is_open()) {
        Logger::logFatal("Unable to open file '%s' -- inventory WILL BE LOST!", file_name.c_str());
        return -1;
    }

    file << "Name,ID,Category,Sub-Category,Location,Quantity,Backorder,Sale Price,Tax,Total "
            "Price,Buy Cost,Profit,Expiration Date"
         << std::endl;

    for (mit = active_inventory->inv_by_name.begin(); mit != active_inventory->inv_by_name.end(); mit++) {
        mit->second->printCSV(file);
        file << std::endl;
    }

    file.close();
    Logger::logInfo("Inventory written to '%s'.", file_name.c_str());

    sale_list->save();

    return 0;
}

bool InventoryManager::userLogin() {
    current_user = login->userInput();
    login->outputCSV();

    if (current_user == NULL) return false;

    Logger::logTrace("User %s logged in.", current_user->name.c_str());

    return true;
}

bool InventoryManager::updatePermission(std::string name, std::string account) {
    if (login->changePermission(name, account, current_user) == true) {
        std::cout << name << " updated to " << account << std::endl;
        return true;
    }

    Logger::logError("Unable to update user '%s' to account type '%s'.", name.c_str(), account.c_str());

    return false;
}

void InventoryManager::makeTransaction() {
    sale_list->transaction_by_order[sale_list->curr_transaction]->processTransaction(active_inventory);
}