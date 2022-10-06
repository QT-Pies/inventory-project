#ifndef PERISHABLEITEM_HPP
#define PERISHABLEITEM_HPP

#include "Date.hpp"
#include "Item.hpp"

class PerishableItem : public Item {
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
   * @param string Expiration date of PerishableItem
   */
  PerishableItem(const std::string&, const std::string&, unsigned long, unsigned long, double, double, double,
                 const std::string&);

  /* Destructor; does nothing */
  ~PerishableItem() override;

  /* Prints out PerishableItem to standard output */
  void print() override;

 private:
  friend class ActiveInventory;

 protected:
  Date expiration_date;
};

#endif