#ifndef ITEM_HPP
#define ITEM_HPP

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

class Item {
   public:
    /*
     * @brief Constructs an Item with the given values
     * @param std::string Name
     * @param std::string Category
     * @param std::string Sub-Category
     * @param unsigned-long Quantity
     * @param unsigned-long ID
     * @param double Price
     * @param double Cost for store to purchase
     * @param double Tax
     */
    Item(const std::string&, const std::string&, const std::string&, unsigned long, unsigned long, double, double,
         double);

    /* @brief Destructor; does nothing */
    virtual ~Item() = default;

    /*
     * @brief Virtual print method that inherited classes will implement.
     */
    virtual void print() = 0;

    /*
     * @brief Virtual printCSV method that inherited classes will implement.
     * @param std::ofstream& ofstream to write to
     */
    virtual void printCSV(std::ofstream&) = 0;

   private:
    friend class ActiveInventory;
    friend class InventoryManager;

   protected:
    std::string name;
    std::string category;
    std::string sub_category;
    unsigned long quantity;
    unsigned long id;
    double sale_price;
    double buy_cost;
    double tax;
    double total_price;
    double profit;
};

#endif
