#include "InventoryManager.hpp"

InventoryManager::InventoryManager(const bool cli, const std::string file)
{
	command_line = cli;
	file_name = file;
}

InventoryManager::~InventoryManager()
{
	/* using smart pointer for active inventory so no deletion neccessary */
}

/* gets command line input from user and calls methods from active inventory class */
int InventoryManager::userInput()
{
	char argument;
	std::string name, category, value;
	unsigned long id; 
	
	if (command_line == false) {
        fprintf(stderr, "Command line is currently set to false\n");
        return -1;
    }
	
	std::cout << "\n(A)dd, (R)emove, (U)pdate, or (Q)uit: ";
	std::cin >> argument;	

	/* switch on argument specified from user and then prompt them accordingly for further input */
	switch(argument)
	{
		case 'A':
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			
			std::cout << "Name Perishable/NonPerishable ID: ";
			std::cin >> name >> category >> id;

			if (active_inventory->addItem(name, category, id) != -1) {
				std::cout << "Added " << name << " of type " << category << std::endl;
			}
			break;

		case 'R':
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			std::cout << "Name: ";
			std::cin >> name;

			if (active_inventory->removeItem(name) != -1) {
				std::cout << "Removed " << name << std::endl;
			} 
			break;

		case 'U':
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			
			std::cout << "Name Field Value: ";
			std::cin >> name >> category >> value;
			
			if (active_inventory->updateItem(name, category, value) != -1) {
				std::cout << "Updated " << category << " of " << name << " to " << value << std::endl;
			}
			break;
		case 'Q':
			printf("Quitting\n");
			return -1;
		default:
			std::cout << "Usage: <(A)dd | (R)emove | (U)pdate>" << std::endl;
			break;
	}

	std::cin.clear();
	std::cin.ignore(10000, '\n');
    
	return 0;
}

/*uses ActiveInventory functions to create items from a csv file*/
void InventoryManager::readCSVFile(const std::string &file)
{
	std::string name, str_id, cat, sub_cat, qty, sale_price;
	std::string tax, total_price, buy_cost, profit, exp, tmp_line; 
	unsigned long id;
	
	std::ifstream csv_file(file);

	if(!csv_file.is_open()) std::cout << "ERROR: unable to open file" << '\n';
	
	/* This skips the first line for you. */
	std::getline(csv_file, tmp_line);

	while(csv_file.good()){

		/*reading in the csv info, converting types*/
		getline(csv_file, name, ',');

		/*exit the loop if we don't read in a new name.*/
		if (!csv_file.good()) break;

		getline(csv_file, str_id, ',');
		id = std::stoul(str_id);
		getline(csv_file, cat, ',');
		getline(csv_file, sub_cat, ',');
		getline(csv_file, qty, ',');
		getline(csv_file, sale_price, ',');
		getline(csv_file, tax, ',');
		getline(csv_file, total_price, ',');
		getline(csv_file, buy_cost, ',');
		getline(csv_file, profit, ',');
		getline(csv_file, exp, '\n');

		/* Add the item to the inventory. */
		if (active_inventory->addItem(name, cat, id) != -1) {
			std::cout << "Added " << name << " of type " << cat << std::endl;
		} else {
			fprintf(stderr, "Failed to read in item %s with ID %lu.\n", name.c_str(), id);
		}

		/* Update all the item categories */
		active_inventory->updateItem(name, "sub_category", sub_cat);
		active_inventory->updateItem(name, "quantity", qty);
		active_inventory->updateItem(name, "sale_price", sale_price);
		active_inventory->updateItem(name, "buy_cost", buy_cost);
		active_inventory->updateItem(name, "tax", tax);
		active_inventory->updateItem(name, "total_price", total_price);
		active_inventory->updateItem(name, "profit", profit);
		if (cat == "Perishable") {
			active_inventory->updateItem(name, "expiration_date", exp);
		}

		/* Test to see if we successfully read in item. */
		auto item_ptr = active_inventory->searchByName(name);

		if (item_ptr == NULL) {
    		fprintf(stderr, "Failed to read item %s that we just created.\n", name.c_str());
		}
	}
}

/* traverse active_memory and output content to file */
int InventoryManager::fileOutput()
{
	std::ofstream file;
	std::map<std::string, std::shared_ptr<Item> >::iterator mit;

	file.open(file_name);

	if (!file.is_open()) {
		fprintf(stderr, "File %s is unable to open", file_name.c_str());
		return -1;
	}

	file << "Name,ID,Category,Sub-Category,Quantity,Sale Price,Tax,Total Price,Buy Cost,Profit,Expiration Date" << std::endl;

	for (mit = active_inventory->inv_by_name.begin(); mit != active_inventory->inv_by_name.end(); mit++) {
		mit->second->printCSV(file);
		file << std::endl;
	}

	file.close();

	std::cout << "Inventory written to " << file_name << std::endl;
	return 0;
}

