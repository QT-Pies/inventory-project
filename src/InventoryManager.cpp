#include "InventoryManager.hpp"

InventoryManager::InventoryManager(const bool cli, const std::string file) {
    command_line = cli;
    file_name = file;
    sale_list->loadSales(file);
    sales_comp->setup(sale_list);
}

InventoryManager::~InventoryManager() {
    fileOutput();
    login->outputCSV();
}

int InventoryManager::userInput() {
    std::string argument;
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

    std::cout << "\n(A)dd, (R)emove, (U)pdate, (S)ale, (C)hange Permissions, (CS)Compare Sales, (P)rint, (L)ogout, or "
                 "(Q)uit: ";
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
            sales_comp->printComparison("LastXYears", x);
        } else if (category == "Last_Month") {
            sales_comp->printComparison("LastMonth", 0);
        } else if (category == "Last_7_days") {
            sales_comp->printComparison("Last7Days", 0);
        } else if (category == "Yesterday") {
            sales_comp->printComparison("Yesterday", 0);
        }

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

        std::cout << "Buyer | Seller\n";
        std::cin >> buyer >> seller;
        std::cout << "Enter Q for Item name or 0 for Quantity Sold to stop reading sales in the transaction\n";

        sale_list->userTransaction(sale_list->curr_sale_id, buyer, seller);

        while (true) {
            std::cout << "Item Name: ";
            std::cin >> name;

            if (name == "Q" || name == "q") break;

            std::cout << "Quantity Sold: ";
            std::cin >> quantity;

            if (quantity == "0") break;

            auto item_ptr = active_inventory->searchByName(name);

            if (item_ptr != NULL) {
                sale_list->transaction_by_order[sale_list->curr_transaction]->addSale(
                    sale_list->curr_sale_id, item_ptr->id, stoul(quantity), item_ptr->sale_price);
                valid_transaction = true;
            } else
                Logger::logWarn("Invalid item -- continuing to read.");
        }

        /* if no valid sales are added to the transaction, then it is deleted, once proper delete feture is added
         * this will be changed */
        if (valid_transaction == false) {
            Logger::logError("Invalid transaction -- no valid sales were input.  Continuing to read.");
            sale_list->transaction_by_order.pop_back();
            sale_list->curr_transaction--;
        } else {
            sale_list->curr_sale_id++;
            makeTransaction();
            Logger::logTrace("User %s entered a transaction.", current_user->name.c_str());
        }
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