#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "ActiveInventory.hpp"
#include "Logger.hpp"
#include "Login.hpp"
#include "NonPerishableItem.hpp"
#include "PerishableItem.hpp"
#include "Sales.hpp"

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
     * @return 0 on success, -1 on failure
     */
    int userInput();

    /*
     * @brief Reads in CSV file and stores it into active_inventory
     */
    void readCSVFile();

    /*
     * @brief Saves the current inventory to disk
     * @return 0 on success, -1 on failure
     */
    int fileOutput();

    /*
     * @brief call userInput in Login class
     * @return return true if successful login and false if not
     */
    bool userLogin();

    /*
     * @brief call updateUser in User class
     * @return return true if successful and false if not
     * @param std::string username
     * @param std::string account_type
     */
    bool updatePermission(std::string, std::string);

   private:
    bool command_line;
    std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
    std::shared_ptr<Login> login{new Login};
    std::shared_ptr<User> current_user;
    std::shared_ptr<SaleList> sale_list{new SaleList};
    std::string file_name;
};

#endif
