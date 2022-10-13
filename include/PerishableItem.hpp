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
   * @param unsigned-long Quantity
   * @param unsigned-long ID
   * @param double Price
   * @param double Cost for store to purchase
   * @param double Tax
   * @param std::string Expiration date
  */
  PerishableItem(const std::string&, const std::string&, const std::string&,
                 unsigned long, unsigned long, double, double, double,
                 const std::string&);

  /* @brief Destructor; does nothing */
  ~PerishableItem() override;

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

 protected:
  Date expiration_date;
};

#endif
