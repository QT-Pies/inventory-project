#ifndef ITEM_HPP
#define ITEM_HPP

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "HelperFunctions.hpp"

class Item {
   public:
    /*
     * @brief Constructs an Item with the given values
     * @param std::string Name
     * @param std::string Category
     * @param std::string Sub-Category
     * @param std::string Quantity
     * @param std::string ID
     * @param std::string Price
     * @param std::string Cost for store to purchase
     * @param std::string Tax
     */
    Item(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&,
         const std::string&);

    /* @brief Destructor; does nothing */
    virtual ~Item() = default;
    
    /*
     * @brief Validates input and sets value for given key.
     * @param std::string Key / Field to validate for and set.
     * @param std::string Value to set.
     * @return true if valid, false if invalid
    */
    virtual bool setValue(std::string, const std::string&);

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
