#ifndef ACTIVE_INVENTORY_HPP
#define ACTIVE_INVENTORY_HPP

#include <map>
#include <memory>
#include <string>

#include "Item.hpp"

class ActiveInventory {
 public:
  ActiveInventory();

  ~ActiveInventory();

  /*
   * This function will add an item to the inventory maps and return
   * how many items were actually added.
   * If there is an error it will return -1.
   */
  int addItem(std::shared_ptr<Item>);

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
  std::shared_ptr<Item> searchById(unsigned long);

 private:
  friend class InventoryManager;
  /*
   * These maps will store the active inventory by category, by name,
   * and by id for searching purposes.
   */
  std::map<std::string, std::map<std::string, std::shared_ptr<Item> > >
      inv_by_category;
  std::map<std::string, std::shared_ptr<Item> > inv_by_name;
  std::map<unsigned long, std::shared_ptr<Item> > inv_by_id;
};

#endif /* ACTIVE_INVENTORY_HPP */
