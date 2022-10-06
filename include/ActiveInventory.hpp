#ifndef ACTIVE_INVENTORY_HPP
#define ACTIVE_INVENTORY_HPP

#include <map>
#include <memory>
#include <string>

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
     * @param string Name of Item
     * @param string Category of Item (Perishable | NonPerishable)
     * @param unsigned-long ID of Item
     */
    int addItem(const std::string, const std::string, const unsigned long);

    /*
     * This function will remove an item from the inventroy maps based
     * on the given string name, and return how many items were actually
     * removed. If there is an error it will return -1.
     * @param string Name of Item to remove
     */
    int removeItem(std::string);

    /* This function will update an existing item based on given item
     * name and property name. It will return the number of fields
     * updated. If there is an error it will return a -1.
     * @param string Name of Item
     * @param string Field to update (quantity, sale_price, etc: see Item.hpp)
     * @param string New value of field
     */
    int updateItem(std::string, std::string, std::string);

    /*
     * This function will look up an item based on it's name. Returns
     * NULL if the item doesn't exist.
     * @param string Name to search for
     */
    std::shared_ptr<Item> searchByName(std::string);

    /*
     * This function will look up an item based on it's id. Returns
     * NULL if the item doesn't exist.
     * @param unsigned-long ID to search for
     */
    std::shared_ptr<Item> searchById(unsigned long);

   private:
    /*
     * These maps will store the active inventory by category, by name,
     * and by id for searching purposes.
     */
    std::map<std::string, std::map<std::string, std::shared_ptr<Item> > > inv_by_category;
    std::map<std::string, std::shared_ptr<Item> > inv_by_name;
    std::map<unsigned long, std::shared_ptr<Item> > inv_by_id;
};

#endif /* ACTIVE_INVENTORY_HPP */
