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
    int addItem(const std::string, const std::string);

	/*
	 * This function will remove an item from the inventroy maps based 
	 * on the given string name, and return how many items were actually 
	 * removed. If there is an error it will return -1.
	 */
	int removeItem(std::string);

	/* These functions will update an existing item based on given item
	 * name and property name. It will return the number of fields 
	 * updated. If there is an error it will return a -1.
	 */
	int updateItem(std::string, std::string, std::string);

    private:	
	
	/*
	 * These maps will store the active inventory by category and by name
	 * for searching purposes.
	 */
        std::map<std::string, std::map<std::string, std::shared_ptr<Item> > > inv_by_category;
        std::map<std::string, std::shared_ptr<Item> > inv_by_name;

};

#endif /* ACTIVE_INVENTORY_HPP */

