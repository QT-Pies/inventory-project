#ifndef ACTIVE_INVENTORY_HPP
#define ACTIVE_INVENTORY_HPP

#include <string>
#include <map>
#include <memory>
#include "Item.hpp"

class ActiveInventory {
    public:
        
	ActiveInventory();

	/*
	 * This constructor will call the file input function on the given
	 * file name.
	 */
	ActiveInventory(std::string);

	~ActiveInventory();

	/* 
         * This function will add an item to the inventory maps and return
	 * how many items were actually added.
	 * If there is an error it will return -1.
         */
        int addItem(const std::string, const std::string, const unsigned int);

	/*
	 * This function will remove an item from the inventroy maps based 
	 * on the given string name, and return how many items were actually 
	 * removed. If there is an error it will return -1.
	 */
	int removeItem(std::string);

	/* This function will update an existing item based on given item
	 * name and property name. It will return the number of fields 
	 * updated. If there is an error it will return a -1.
	 */
	int updateItem(std::string, std::string, std::string);

        /*
	 * This function will look up an item based on it's name. Returns
	 * NULL if the item doesn't exist.
	 */
	std::shared_ptr<Item> searchByName(std::string);

	/*
	 * This function will look up an item based on it's id. Returns
	 * NULL if the item doesn't exist.
	 */
	std::shared_ptr<Item> searchById(unsigned int);

    private:

		friend class InventoryManager;
	/*
	 * These maps will store the active inventory by category, by name,
	 * and by id for searching purposes.
	 */
        std::map<std::string, std::map<std::string, std::shared_ptr<Item> > > inv_by_category;
        std::map<std::string, std::shared_ptr<Item> > inv_by_name;
	    std::map<unsigned int, std::shared_ptr<Item> > inv_by_id;

};

#endif /* ACTIVE_INVENTORY_HPP */

