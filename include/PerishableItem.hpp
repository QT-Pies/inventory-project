#ifndef PERISHABLEITEM_HPP
#define PERISHABLEITEM_HPP

#include "Date.hpp"
#include "Item.hpp"

class PerishableItem : public Item {
   public:
    /*
     * @brief Constructs a NonPerishableItem with the given values
     * @param std::string Name
     * @param std::string Category
     * @param std::string Sub-Category
     * @param std::string Location
     * @param std::string Quantity
     * @param std::string Backorder
     * @param std::string ID
     * @param std::string Price
     * @param std::string Cost for store to purchase
     * @param std::string Tax
     * @param std::string Expiration date
     */
    PerishableItem(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&,
                   const std::string&, const std::string&, const std::string&, const std::string&, const std::string&,
                   const std::string&);

    /* @brief Destructor; does nothing */
    ~PerishableItem() override;

    /*
     * @brief Prints the Item in a human friendly way
     */
    void print() override;

    /*
     * @brief Override Item::setValue() to support Perishable data members (expiration_date).
     * @brief Throws exception if invalid.
     * @param std::string Key to set
     * @param std::string Value to set key with
     */
    void setValue(std::string, const std::string&) override;

    /*
     * @brief Prints the Item as a CSV entry
     * @param std::ofstream ofstream to write to
     */
    void printCSV(std::ofstream&) override;

   private:
    friend class ActiveInventory;

   protected:
    Date expiration_date;
};

#endif
