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
   * @brief This function will add an item to the inventory maps and return
   * how many items were actually added.
   * @param std::shared_ptr<Item> Item to insert
   * @return 0 on success, -1 on failure
   */
  int addItem(std::shared_ptr<Item>);

  /*
   * @brief This function will remove an item from the inventroy maps based
   * on the given string name, and return how many items were actually
   * removed.
   * @param std::string Name of Item to remove
   * @return 0 on success, -1 on failure
   */
  int removeItem(std::string);

  /* @brief This function will update an existing item based on given item
   * name and property name. It will return the number of fields
   * updated.
   * @param std::string Name of Item to update
   * @param std::string Field on Item to update
   * @param std::string New value for field
   * @return 0 on success, -1 on failure
   */
  int updateItem(std::string, std::string, std::string);

  /*
   * @brief This function will look up an item based on it's name.
   * @param std::string Name of Item to search for
   * @return std::shared_ptr<Item> to Item, or NULL if Item not found
   */
  std::shared_ptr<Item> searchByName(std::string);

  /*
   * @brief This function will look up an item based on it's id.
   * @param unsigned-long ID of Item to search for
   * @return std::shared_ptr<Item> to Item, or NULL if Item not found
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
