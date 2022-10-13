#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include "ActiveInventory.hpp"

class InventoryManager {
 public:
  /*
   * @brief Constructor; specifies whether CLI mode is enabled, and the file to
   * open.
   * @param bool CLI mode
   * @param std::string Inventory file to read in
   */
  InventoryManager(const bool, const std::string);

  /* @brief Destructor; does nothing */
  ~InventoryManager();

  /*
   * @brief Reads standard input from user
   */
  int userInput();

  /*
   * @brief Reads in CSV file and stores it into active_inventory
   */
  void readCSVFile();

  /*
   * @brief Saves the current inventory to disk
   */
  int fileOutput();

 private:
  bool command_line;
  std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
  std::string file_name;
};

#endif
