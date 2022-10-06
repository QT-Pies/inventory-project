#ifndef INVENTORYGENERATOR_HPP
#define INVENTORYGENERATOR_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "CSVEntry.hpp"

class InventoryGenerator {
 public:
  /* InventoryGenerator constructor; initializes variable to default values */
  InventoryGenerator();

  /*
   * Generates a file with the specified number of unspecified, non-perishable, and perishable items
   * @param string File name
   * @param unsigned-long Number of unknown Items
   * @param unsigned-long Number of NonPerishableItems
   * @param unsigned-long Number of PerishableItems
   */
  void generateFile(const std::string&, unsigned long, unsigned long, unsigned long);

  /*
   * Adds the given key to the bad key set
   * @param string - Key/Field to add to bad key set
   */
  void setBadKey(const std::string&);

  /*
   * Set the random factor to not use the default of 2.
   * @param int New random factor -- higher the number, lower the chance
   */
  void setRandomFactor(const int&);

  /* Toggle whether bad-input is random */
  void toggleRandom();

 protected:
  /* Generates an Item */
  std::shared_ptr<CSVEntry> generateItem();

  /* Generates an NonPerishableItem */
  std::shared_ptr<CSVEntry> generateNonPerishableItem();

  /* Generates a PerishableItem */
  std::shared_ptr<CSVEntry> generatePerishableItem();

  /* Returns whether the given key is in the bad set */
  bool isBadKey(const std::string&);

  /* Expected columns in CSV inventory, chars for random names. */
  const std::vector<std::string> columns = {"Name",           "ID",  "Category",    "Sub-Category", "Quantity",
                                            "Sale Price",     "Tax", "Total Price", "Buy Cost",     "Profit",
                                            "Expiration Date"};
  const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  std::set<std::string> bad_keys;
  unsigned long id_count;
  int factor;
  bool random;
  bool bad;
  std::ofstream file;
};

#endif