#include "InventoryManager.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "NonPerishableItem.hpp"
#include "PerishableItem.hpp"

InventoryManager::InventoryManager(const bool cli, const std::string file) {
    command_line = cli;
    file_name = file;
}

InventoryManager::~InventoryManager() { /* using smart pointer for active inventory so no deletion neccessary */
}

int InventoryManager::userInput() {
    char argument;
    std::string name, category, sub_category, expiration, value;
    unsigned long id, quantity;
    double sale_price, buy_price, tax;
    std::shared_ptr<Item> new_item;

    if (command_line == false) {
        fprintf(stderr, "Command line is currently set to false\n");
        return -1;
    }

    std::cout << "\n(A)dd, (R)emove, (U)pdate, (P)rint, or (Q)uit: ";
    std::cin >> argument;

    /* switch on argument specified from user and then prompt them accordingly for
     * further input */
    switch (argument) {
        case 'A':
        case 'a':
            std::cin.clear();
            std::cin.ignore(10000, '\n');

            std::cout << "Name Perishable/NonPerishable SubCategory Quantity ID SalePrice "
                         "CostOfGood Tax ExpirationDate (Enter -1000000 if unsure): ";
            std::cin >> name >> category >> sub_category >> quantity >> id >> sale_price >> buy_price >> tax >>
                expiration;
            if (category == "Perishable") {
                new_item = std::make_shared<PerishableItem>(name, category, sub_category, quantity, id, sale_price,
                                                            buy_price, tax, expiration);
            } else if (category == "NonPerishable") {
                new_item = std::make_shared<NonPerishableItem>(name, category, sub_category, quantity, id, sale_price,
                                                               buy_price, tax);
            } else {
                fprintf(stderr, "Invalid category\n");
                break;
            }

            if (active_inventory->addItem(new_item) != -1) {
                std::cout << "Added " << name << " of type " << category << std::endl;
            }
            break;

        case 'R':
        case 'r':
            std::cin.clear();
            std::cin.ignore(10000, '\n');

            std::cout << "Name: ";
            std::cin >> name;

            if (active_inventory->removeItem(name) != -1) {
                std::cout << "Removed " << name << std::endl;
            }
            break;

        case 'U':
        case 'u':
            std::cin.clear();
            std::cin.ignore(10000, '\n');

            std::cout << "Name Field Value: ";
            std::cin >> name >> category >> value;

            if (active_inventory->updateItem(name, category, value) != -1) {
                std::cout << "Updated " << category << " of " << name << " to " << value << std::endl;
            }
            break;

        case 'P':
        case 'p':
            std::cin.clear();
            std::cin.ignore(10000, '\n');

            std::cout << "All | Perishable | NonPerishable | Item Name: ";
            std::cin >> category;
            active_inventory->printItems(category);
            break;

        case 'Q':
        case 'q':
            printf("Quitting\n");
            return -1;
        default:
            std::cout << "Usage: <(A)dd | (R)emove | (U)pdate | (P)rint | (Q)uit>" << std::endl;
            break;
    }

    std::cin.clear();
    std::cin.ignore(10000, '\n');

    return 0;
}

/*uses ActiveInventory functions to create items from a csv file*/
void InventoryManager::readCSVFile() {
    std::string name, str_id, cat, sub_cat, qty, sale_price;
    std::string tax, total_price, buy_cost, profit, exp, tmp_line;
    std::shared_ptr<Item> new_item;

    std::ifstream csv_file(file_name);

    if (!csv_file.is_open()) std::cout << "ERROR: unable to open file" << '\n';

    /* This skips the first line for you. */
    std::getline(csv_file, tmp_line);

    while (csv_file.good()) {
        /*reading in the csv info, converting types*/
        getline(csv_file, name, ',');

        /*exit the loop if we don't read in a new name.*/
        if (!csv_file.good()) break;

        getline(csv_file, str_id, ',');
        getline(csv_file, cat, ',');
        getline(csv_file, sub_cat, ',');
        getline(csv_file, qty, ',');
        getline(csv_file, sale_price, ',');
        getline(csv_file, tax, ',');
        getline(csv_file, total_price, ',');
        getline(csv_file, buy_cost, ',');
        getline(csv_file, profit, ',');
        getline(csv_file, exp, '\n');

        /* Create the Item to be added. */
        if (cat == "Perishable") {
            new_item = std::make_shared<PerishableItem>(name, cat, sub_cat, stoul(qty), stoul(str_id), stod(sale_price),
                                                        stod(buy_cost), stod(tax), exp);
        } else if (cat == "NonPerishable") {
            new_item = std::make_shared<NonPerishableItem>(name, cat, sub_cat, stoul(qty), stoul(str_id),
                                                           stod(sale_price), stod(buy_cost), stod(tax));
        } else {
            fprintf(stderr, "Invalid category.\n");
        }

        /* Add the item to the active inventory. */
        active_inventory->addItem(new_item);

        /* Test to see if we successfully read in item. */
        auto item_ptr = active_inventory->searchByName(name);

        if (item_ptr == NULL) {
            fprintf(stderr, "Failed to read item %s that we just created.\n", name.c_str());
        }
    }
}

int InventoryManager::fileOutput() {
    std::ofstream file;
    std::map<std::string, std::shared_ptr<Item>>::iterator mit;

    file.open(file_name);

    if (!file.is_open()) {
        fprintf(stderr, "File %s is unable to open", file_name.c_str());
        return -1;
    }

    file << "Name,ID,Category,Sub-Category,Quantity,Sale Price,Tax,Total "
            "Price,Buy Cost,Profit,Expiration Date"
         << std::endl;

    for (mit = active_inventory->inv_by_name.begin(); mit != active_inventory->inv_by_name.end(); mit++) {
        mit->second->printCSV(file);
        file << std::endl;
    }

    file.close();

    std::cout << "Inventory written to " << file_name << std::endl;
    return 0;
}

bool InventoryManager::userLogin() {

    login->readCSV();
    auto user = login->userInput();
    
    if(user == NULL) return false;

    return true;
}