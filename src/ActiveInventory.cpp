#include "../include/ActiveInventory.hpp"

ActiveInventory::ActiveInventory() 
{
    inv_by_category = std::make_unique<map <string, map<string, 
	shared_ptr<Item> > > (map<string, map< string, std::shared_ptr<Item> > >);

    inv_by_name = std::make_unique<map <string, std::shared_ptr<Item> > 
	    (map<string, std::shared_ptr<Item> >);
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

int ActiveInventory::addItem(std::string name, std::string category) 
{
    /* Check if the category is a valid category. */
    if (category == "Perishable") {
        auto new_item = make_shared<PerishableItem>(name, 0, 0, 0, 0, 0, "0");
	inv_by_name->insert(name, new_item);
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
    return -1;
}
