#include "ActiveInventory.hpp"

#include "Date.cpp"
#include "Item.cpp"
#include "NonPerishableItem.cpp"
#include "PerishableItem.cpp"

ActiveInventory::ActiveInventory() {
    std::make_unique<std::map<std::string, std::map<std::string, std::shared_ptr<Item>>>>(inv_by_category);

    std::make_unique<std::map<std::string, std::shared_ptr<Item>>>(inv_by_name);

    std::make_unique<std::map<unsigned long, std::shared_ptr<Item>>>(inv_by_id);
};

ActiveInventory::~ActiveInventory(){
    // All objects of this class are smart pointers that will free themselves.
};

int ActiveInventory::addItem(std::shared_ptr<Item> new_item) {
    if (inv_by_name.find(new_item->name) != inv_by_name.end())  // Check if item is already in the inventory.
    {
        Logger::logError("Item '%s' is already in the inventory.", new_item->name.c_str());
        return -1;
    } else if (inv_by_id.find(new_item->id) != inv_by_id.end()) {
        Logger::logError("ID '%lu' is already an ID for another Item.", new_item->id);
        return -1;
    } else {
        inv_by_name[new_item->name] = new_item;
        inv_by_category[new_item->category][new_item->name] = new_item;
        inv_by_id[new_item->id] = new_item;
        inv_by_location[new_item->location][new_item->name] = new_item;
        return 1;
    }
    return -1;  // This shouldn't be reached.
}

int ActiveInventory::removeItem(std::string name) {
    std::string cat, loc;
    std::shared_ptr<Item> for_deletion;
    if (inv_by_name.find(name) != inv_by_name.end()) {
        for_deletion = inv_by_name.find(name)->second;
        cat = for_deletion->category;
        loc = for_deletion->location;
        inv_by_name.erase(name);
        inv_by_id.erase(for_deletion->id);
        inv_by_category[cat].erase(inv_by_category.find(cat)->second.find(name));
        if (inv_by_category.find(cat)->second.size() <= 0) {
            inv_by_category.erase(cat);  // If the map keyed off the category is empty
                                         // we remove it from the map.
        }

        inv_by_location[loc].erase(inv_by_location.find(loc)->second.find(name));
        if (inv_by_location.find(loc)->second.size() <= 0) {
            inv_by_location.erase(loc);
        }

        return 1;
    } else {
        Logger::logError("Item '%s' was not found in the inventory.", name.c_str());
        return -1;
    }

    return -1;  // If this is reached an error has occurred.
}

int ActiveInventory::updateItem(std::string item_name, std::string field, std::string value) {
    try {
        auto item = searchByName(item_name);

        /* Convert string to lowercase to allow support for FIELD or field */
        lowerCaseString(field);

        /* Throw exception if couldn't find item. */
        if (item == NULL) {
            throw std::invalid_argument(item_name + " is not in the inventory.");
        }

        /* If field is Name, verify it is not already taken. */
        if (field == "name") {
            if (searchByName(value) != NULL) {
                throw std::invalid_argument("Name '" + value + "' is already used by another Item.");
            }

            /* Remove existing entry for Item in inventory */
            inv_by_name.erase(inv_by_name.find(item->name));
            inv_by_category[item->category].erase(inv_by_category[item->category].find(item->name));

            /* Update item name and re-insert */
            item->setValue(field, value);
            inv_by_name[item->name] = item;
            inv_by_category[item->category][item->name] = item;

        } /* If field is ID, verify it is not already taken. */
        else if (field == "id") {
            auto long_id = toUnsignedLong(value);

            /* Check that ID is not taken */
            if (searchById(long_id) != NULL) {
                throw std::invalid_argument("ID '" + value + "' is already used by another Item.");
            }

            /* Remove old ID, set new, re-insert. */
            inv_by_id.erase(inv_by_id.find(item->id));
            item->setValue(field, value);
            inv_by_id[item->id] = item;
        } else if (field == "category") {
            throw std::invalid_argument("You can only set category when creating an Item.");
        } else if (field == "location") {
            throw std::invalid_argument("You can only set location when creating an Item.");
        } /* Otherwise, all other fields shouldn't need any additional checks. */
        else {
            item->setValue(field, value);
        }
    } catch (std::exception& e) {
        Logger::logError(e.what());
        return -1;
    }

    return 0;
}

std::shared_ptr<Item> ActiveInventory::searchByName(std::string item_name) {
    std::shared_ptr<Item> ret;

    /* If the item is in the map we return a shared_ptr to it, otherwise we return
     * NULL. */
    if (inv_by_name.find(item_name) != inv_by_name.end()) {
        ret = inv_by_name[item_name];
        return ret;
    } else {
        return NULL;
    }
}

std::shared_ptr<Item> ActiveInventory::searchById(unsigned long item_id) {
    std::shared_ptr<Item> ret;

    /* If the id is in the map we return a shared_ptr to the item, otherwise we
     * return NULL. */
    if (inv_by_id.find(item_id) != inv_by_id.end()) {
        ret = inv_by_id[item_id];
        return ret;
    } else {
        return NULL;
    }
}

void ActiveInventory::printItems(std::string field, std::string value) {
    std::shared_ptr<Item> item;

    if (field == "Location") {
        auto it = inv_by_location.find(value);
        if (it != inv_by_location.end()) {
            printHead();
            for (auto loc_it = it->second.begin(); loc_it != it->second.end(); loc_it++) {
                loc_it->second->print();
            }
        } else {
            Logger::logWarn("Location '%s' does not exist.", value.c_str());
        }

        return;
    } else {
        if (value == "All") {
            /* if map is empty print error message and return*/
            if (inv_by_id.size() == 0) {
                Logger::logWarn("Inventory is currently empty");
                return;
            }
            printHead();
            for (auto id_it = inv_by_id.begin(); id_it != inv_by_id.end(); id_it++) {
                id_it->second->print();
            }

        } else if (value == "Perishable" || value == "NonPerishable") {
            auto cat_it = inv_by_category.find(value);

            /*if category is empty print error message and return*/
            if (cat_it == inv_by_category.end()) {
                Logger::logWarn("Category '%s' is currently empty.", value.c_str());
                return;
            }
            printHead();
            for (auto name_it = cat_it->second.begin(); name_it != cat_it->second.end(); name_it++) {
                name_it->second->print();
            }

        } else {
            item = searchByName(value);

            /* if item does not exist then print error message and return */
            if (item == NULL) {
                Logger::logWarn("Item '%s' is not in the inventory.", value.c_str());
                return;
            }
            printHead();
            item->print();
            std::cout << std::endl;
        }
    }
}

void ActiveInventory::printHead() {
    std::cout << std::left << std::setw(7) << "ID" << std::left << std::setw(40) << "ITEM" << std::left << std::setw(17)
              << "CATEGORY" << std::left << std::setw(15) << "LOCATION" << std::left << std::setw(10) << "STOCK"
              << std::left << std::setw(10) << "BACKORDER" << std::left << std::setw(15) << "PURCHASE_COST" << std::left
              << std::setw(15) << "SALE-PRICE" << std::left << std::setw(15) << "TAX-ON-ITEM" << std::left
              << std::setw(15) << "TOTAL-PRICE" << std::left << std::setw(10) << "PROFIT" << std::left << std::setw(10)
              << "EXPIRATION" << std::endl;
}