#include "../include/ActiveInventory.hpp"
#include "Date.cpp"
#include "Item.cpp"
#include "NonPerishableItem.cpp"
#include "PerishableItem.cpp"

ActiveInventory::ActiveInventory() 
{
    std::make_unique<std::map <std::string, std::map<std::string,
	std::shared_ptr<Item> > > >(inv_by_category);

    std::make_unique<std::map <std::string, std::shared_ptr<Item> > >(inv_by_name);
};

ActiveInventory::ActiveInventory(std::string file_name) 
{
    //TODO: Here we will call the inputFile function when it is made.
    (void)file_name;
    ActiveInventory();
};

ActiveInventory::~ActiveInventory() 
{
    //All objects of this class are smart pointers that will free themselves.
};

int ActiveInventory::addItem(const std::string name, const std::string category)
{
    if (inv_by_name.find(name) != inv_by_name.end()) //Check if item is already in the inventory.
    {
        fprintf(stderr, "%s is already in the inventory.\n", name.c_str());
        return 0;
    } else {
        /* Check if the category is a valid category. */
        if (category == "Perishable") {
            auto new_item = std::make_shared<PerishableItem>(name, 0, 0, 0, 0, 0, Date(0));
            inv_by_name[name] = new_item;
            inv_by_category[category].second.insert(name, new_item);
            return 1;
        } else if (category == "NonPerishable") {
            auto new_item = make_shared<NonPerishableItem>(name, 0, 0, 0, 0, 0);
            inv_by_name->insert(name, new_item);
            inv_by_category[category].second.insert(name, new_item);
            return 1;
        } else {
            fprintf(stderr, "Invalid category given: %s\n", category);
            return -1;
        }
    }
    return -1;
}

int ActiveInventory::removeItem(std::string name)
{
    std::string cat;
    Item *for_deletion;
    if (inv_by_name.find(name) != inv_by_name.end())
    {
        for_deletion = inv_by_category.find(name)->second();
        cat = for_deletion->category;
        inv_by_name.erase(name);
        inv_by_category.erase(inv_by_category.find(cat)->second().find(name));
        if (inv_by_category.find(cat)->second()->size() <= 0)
        {
            inv_by_category.erase(cat); //If the map keyed off the category is empty we remove it from the map.
        }
        return 1;
    } else
    {
        fprintf(stderr, "%s is not in current inventory.\n", name);
        return -1;
    }

    return -1; //If this is reached an error has occurred.
}

int ActiveInventory::updateItem(std::string item_name, std::string field, std::string value)
{
    std::string cat;
    if (inv_by_name.find(item_name) == inv_by_name.end())
    {
        fprintf(stderr, "%s is not in the inventory.\n", name);
        return -1;
    }

    cat = inv_by_name.find(item_name)->second()->category;

    //Here we find the item and field to update.
    if (cat == "Perishable")
    {
        PerishableItem *to_update = inv_by_name.find(item_name)->second();
        switch(field)
        {
            case "name": //If the name is to be changed we will have to re-enter it into the maps.
                printf("To change the name you have to recreate the item with the new name.");
                break;
            case "sub_category":
                to_update->sub_category = value;
                break;
            case "quantity":
                to_update->quantity = stoi(value);
                break;
            case "id":
                to_update->id = stoi(value);
                break;
            case "sale_price":
                to_update->sale_price = stod(value);
                break;
            case "buy_cost":
                to_update->buy_cost = stod(value);
                break;
            case "tax":
                to_update->tax = stod(value);
                break;
            case "total_price":
                to_update->total_price = stod(value);
                break;
            case "profit":
                to_update->profit = stod(value);
                break;
            case "expiration_date":
                to_update->expiration_date = Date(value);
                break;
            default:
                fprintf(stderr, "Invalid field to update.\n");
                return -1;
        }
    } else
    {
        NonPerishableItem *to_update = inv_by_name.find(name)->second();
        switch(field)
        {
            case "name": //If the name is to be changed we will have to re-enter it into the maps.
                printf("To change the name you have to recreate the item with the new name.");
                break;
            case "sub_category":
                to_update->sub_category = value;
                break;
            case "quantity":
                to_update->quantity = stoi(value);
                break;
            case "id":
                to_update->id = stoi(value);
                break;
            case "sale_price":
                to_update->sale_price = stod(value);
                break;
            case "buy_cost":
                to_update->buy_cost = stod(value);
                break;
            case "tax":
                to_update->tax = stod(value);
                break;
            case "total_price":
                to_update->total_price = stod(value);
                break;
            case "profit":
                to_update->profit = stod(value);
                break;
            default:
                fprintf(stderr, "Invalid field to update.\n");
                return -1;
        }
    }
}
