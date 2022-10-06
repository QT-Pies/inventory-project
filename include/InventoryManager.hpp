#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include "ActiveInventory.hpp"

class InventoryManager {
   public:
    /*
     * Constructor; specifies whether CLI mode is enabled
     * @param bool CLI mode
     */
    InventoryManager(const bool);

    /* Destructor; does nothing */
    ~InventoryManager();

    /* Reads standard-input from user */
    int userInput();

   private:
    bool command_line;
    std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
};

#endif
