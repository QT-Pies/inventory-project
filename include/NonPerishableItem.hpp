#ifndef NONPERISHABLEITEM_HPP
#define NONPERISHABLEITEM_HPP

#include "Item.hpp"

class NonPerishableItem : public Item {
   public:
    /*
     * @brief Constructs a NonPerishableItem with the given values
     * @param std::string Name
     * @param std::string Category
     * @param std::string Sub-Category
     * @param unsigned-long Quantity
     * @param unsigned-long ID
     * @param double Price
     * @param double Cost for store to purchase
     * @param double Tax
     */
    NonPerishableItem(const std::string&, const std::string&, const std::string&, unsigned long, unsigned long, double,
                      double, double);

    /* @brief Destructor; does nothing */
    ~NonPerishableItem() override;

    /*
     * @brief Prints the Item in a human friendly way
     */
    void print() override;

    /*
     * @brief Prints the Item as a CSV entry
     * @param std::ofstream ofstream to write to
     */
    void printCSV(std::ofstream&) override;

   private:
    friend class ActiveInventory;
};

#endif
