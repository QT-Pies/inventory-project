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
     * @param std::string Quantity
     * @param std::string Backorder
     * @param std::string ID
     * @param std::string Price
     * @param std::string Cost for store to purchase
     * @param std::string Tax
     */
    NonPerishableItem(const std::string&, const std::string&, const std::string&, const std::string&,
                      const std::string&, const std::string&, const std::string&, const std::string&,
                      const std::string&);

    /* @brief Destructor; does nothing */
    ~NonPerishableItem() override;

    /*
     * @brief Prints the Item in a human friendly way
     */
    void print() override;

    /* Don't need to override setValue because we don't have any extra members. */

    /*
     * @brief Prints the Item as a CSV entry
     * @param std::ofstream ofstream to write to
     */
    void printCSV(std::ofstream&) override;

   private:
    friend class ActiveInventory;
};

#endif
