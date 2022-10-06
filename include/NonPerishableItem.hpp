#ifndef NONPERISHABLEITEM_HPP
#define NONPERISHABLEITEM_HPP

#include "Item.hpp"

class NonPerishableItem : public Item {
   public:
    /*
     * Constructs an item with the given values.
     * @param string Name of item
     * @param string Category of item (Perishable | NonPerishable)
     * @param unsigned-long Quantity of item
     * @param unsigned-long ID of item
     * @param double Price of item
     * @param double Cost for store to purchase item
     * @param double Tax on item
     */
    NonPerishableItem(const std::string&, const std::string&, unsigned long, unsigned long, double, double, double);

    /* Destructor; does nothing. */
    ~NonPerishableItem() override;

    /* Prints out NonPerishableItem to standard output */
    void print() override;

   private:
    friend class ActiveInventory;
};

#endif