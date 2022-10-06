#include "ActiveInventory.hpp"

#include "Date.cpp"
#include "Item.cpp"
#include "NonPerishableItem.cpp"
#include "PerishableItem.cpp"

ActiveInventory::ActiveInventory() {
    std::make_unique<std::map<std::string, std::map<std::string, std::shared_ptr<Item> > > >(inv_by_category);

    std::make_unique<std::map<std::string, std::shared_ptr<Item> > >(inv_by_name);

    std::make_unique<std::map<unsigned long, std::shared_ptr<Item> > >(inv_by_id);
};

ActiveInventory::ActiveInventory(std::string file_name) {
    // TODO: Here we will call the inputFile function when it is made.
    (void)file_name;
    ActiveInventory();
};

ActiveInventory::~ActiveInventory(){
    // All objects of this class are smart pointers that will free themselves.
};

int ActiveInventory::addItem(const std::string name, const std::string category, unsigned long item_id) {
    /* Check if item is already in the inventory */
    if (inv_by_name.find(name) != inv_by_name.end()) {
        fprintf(stderr, "%s is already in the inventory.\n", name.c_str());
        return -1;
    } else if (inv_by_id.find(item_id) != inv_by_id.end()) {
        fprintf(stderr, "%lu is already an id for another Item\n", item_id);
        return -1;
    } else {
        /* Check if the category is a valid category and add it if is is valid. */
        if (category == "Perishable") {
            auto new_item = std::make_shared<PerishableItem>(name, "None", item_id, 0, 0, 0, 0, "0");
            new_item->category = "Perishable";
            inv_by_name[name] = new_item;
            inv_by_category[category][name] = new_item;
            inv_by_id[item_id] = new_item;
            return 1;
        } else if (category == "NonPerishable") {
            auto new_item = std::make_shared<NonPerishableItem>(name, "None", item_id, 0, 0, 0, 0);
            new_item->category = "NonPerishable";
            inv_by_name[name] = new_item;
            inv_by_category[category][name] = new_item;
            inv_by_id[item_id] = new_item;
            return 1;
        } else {
            fprintf(stderr, "Invalid category given: %s\n", category.c_str());
            return -1;
        }
    }
    return -1;
}

int ActiveInventory::removeItem(std::string name) {
    std::string cat;
    std::shared_ptr<Item> for_deletion;
    if (inv_by_name.find(name) != inv_by_name.end()) {
        for_deletion = inv_by_name.find(name)->second;
        cat = for_deletion->category;
        inv_by_name.erase(name);
        inv_by_id.erase(for_deletion->id);
        inv_by_category[cat].erase(inv_by_category.find(cat)->second.find(name));
        if (inv_by_category.find(cat)->second.size() <= 0) {
            // If the map keyed off the category is empty we remove it from the map.
            inv_by_category.erase(cat);
        }
        return 1;
    } else {
        fprintf(stderr, "%s is not in current inventory.\n", name.c_str());
        return -1;
    }

    // If this is reached an error has occurred.
    return -1;
}

int ActiveInventory::updateItem(std::string item_name, std::string field, std::string value) {
    std::string cat;

    if (inv_by_name.find(item_name) == inv_by_name.end()) {
        fprintf(stderr, "%s is not in the inventory.\n", item_name.c_str());
        return -1;
    }

    cat = inv_by_name.find(item_name)->second->category;

    /* Here we find the item and field to update. */
    if (cat == "Perishable") {
        std::shared_ptr<PerishableItem> to_update = std::dynamic_pointer_cast<PerishableItem>(inv_by_name[item_name]);

        // If the name is to be changed we will have to re-enter it into the maps.
        if (field == "name") {
            if (searchByName(value) != NULL) {
                fprintf(stderr, "Cannot change name to %s as it already exists.\n", value.c_str());
            }
            // Remove old name from maps and add the new one.
            else {
                inv_by_name.erase(inv_by_name.find(to_update->name));
                inv_by_category[to_update->category].erase(inv_by_category[to_update->category].find(to_update->name));
                to_update->name = value;
                inv_by_name[to_update->name] = to_update;
                inv_by_category[to_update->category][to_update->name] = to_update;
            }
        } else if (field == "sub_category") {
            to_update->sub_category = value;
        } else if (field == "quantity") {
            to_update->quantity = stoi(value);
        } else if (field == "id") {
            if (searchById(stoi(value)) != NULL) {
                printf("Id %u is already used by another Item.\n", stoi(value));
            } else {
                inv_by_id.erase(inv_by_id.find(to_update->id));
                to_update->id = stoi(value);
                inv_by_id[to_update->id] = to_update;
            }
        } else if (field == "sale_price") {
            to_update->sale_price = stod(value);
        } else if (field == "buy_cost") {
            to_update->buy_cost = stod(value);
        } else if (field == "tax") {
            to_update->tax = stod(value);
        } else if (field == "total_price") {
            to_update->total_price = stod(value);
        } else if (field == "profit") {
            to_update->profit = stod(value);
        } else if (field == "expiration_date") {
            to_update->expiration_date = Date(value);
        } else {
            fprintf(stderr, "Invalid field to update: %s.\n", field.c_str());
            return -1;
        }
    } else {
        std::shared_ptr<NonPerishableItem> to_update =
            std::dynamic_pointer_cast<NonPerishableItem>(inv_by_name[item_name]);

        // If the name is to be changed we will have to re-enter it into the maps.
        if (field == "name") {
            if (searchByName(value) != NULL) {
                fprintf(stderr, "Cannot change name to %s as it already exists.\n", value.c_str());
            }
            // Remove the old name and add the new name.
            else {
                inv_by_name.erase(inv_by_name.find(to_update->name));
                inv_by_category[to_update->category].erase(inv_by_category[to_update->category].find(to_update->name));
                to_update->name = value;
                inv_by_name[to_update->name] = to_update;
                inv_by_category[to_update->category][to_update->name] = to_update;
            }
        } else if (field == "sub_category") {
            to_update->sub_category = value;
        } else if (field == "quantity") {
            to_update->quantity = stoi(value);
        } else if (field == "id") {
            if (searchById(stoi(value)) != NULL) {
                printf("Id %u is already used by another Item.\n", stoi(value));
            } else {
                inv_by_id.erase(inv_by_id.find(to_update->id));
                to_update->id = stoi(value);
                inv_by_id[to_update->id] = to_update;
            }
        } else if (field == "sale_price") {
            to_update->sale_price = stod(value);
        } else if (field == "buy_cost") {
            to_update->buy_cost = stod(value);
        } else if (field == "tax") {
            to_update->tax = stod(value);
        } else if (field == "total_price") {
            to_update->total_price = stod(value);
        } else if (field == "profit") {
            to_update->profit = stod(value);
        } else {
            fprintf(stderr, "Invalid field to update.\n");
            return -1;
        }
    }

    /* This shouldn't be reached */
    return 1;
}

std::shared_ptr<Item> ActiveInventory::searchByName(std::string item_name) {
    std::shared_ptr<Item> ret;

    /* If the item is in the map we return a shared_ptr to it, otherwise we return NULL. */
    if (inv_by_name.find(item_name) != inv_by_name.end()) {
        ret = inv_by_name[item_name];
        return ret;
    } else {
        return NULL;
    }
}

std::shared_ptr<Item> ActiveInventory::searchById(unsigned long item_id) {
    std::shared_ptr<Item> ret;

    /* If the id is in the map we return a shared_ptr to the item, otherwise we return NULL. */
    if (inv_by_id.find(item_id) != inv_by_id.end()) {
        ret = inv_by_id[item_id];
        return ret;
    } else {
        return NULL;
    }
}
