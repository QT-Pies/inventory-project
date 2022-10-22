#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include "ActiveInventory.hpp"
#include "Login.hpp"

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

   private:
    bool command_line;
    std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
    std::shared_ptr<Login> login{new Login};
    std::string file_name;
};

#endif
