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
    InventoryGenerator();

    /*
     * @brief Generates a file with the specified number of unspecified,
     * non-perishable, and perishable items
     * @param string File name
     * @param unsigned-long Number of unknown Items
     * @param unsigned-long Number of NonPerishableItems
     * @param unsigned-long Number of PerishableItems
     */
    void generateFile(const std::string&, unsigned int, unsigned int, unsigned int);

    /*
     * @brief Adds the given key to the bad key set
     * @param string - Key/Field to add to bad key set
     */
    void setBadKey(const std::string&);

    /*
     * @brief Set the random factor to not use the default (2).
     * @param int New random factor -- higher the number, lower the chance.
     */
    void setRandomFactor(const int&);

    /*
     * @brief Toggle whether bad input is random.
     */
    void toggleRandom();

   protected:
    /*
     * @brief Generates an Item
     * @return std::shared_ptr<CSVEntry> with values to match Item
     */
    std::shared_ptr<CSVEntry> generateItem();

    /*
     * @brief Generates a NonPerishableItem
     * @return std::shared_ptr<CSVEntry> with values to match NonPerishableItem
     */
    std::shared_ptr<CSVEntry> generateNonPerishableItem();

    /*
     * @brief Generates a PerishableItem
     * @return std::shared_ptr<CSVEntry> with values to match PerishableItem
     */
    std::shared_ptr<CSVEntry> generatePerishableItem();

    /*
     * @brief Checks whether the given key is in the bad key set
     * @param std::string Key to check
     * @return true if bad key, false if good key
     */
    bool isBadKey(const std::string&);

    /* Expected columns */
    const std::vector<std::string> columns = {"Name",           "ID",  "Category",    "Sub-Category", "Quantity",
                                              "Sale Price",     "Tax", "Total Price", "Buy Cost",     "Profit",
                                              "Expiration Date"};

    /* Chars for random name generation */
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::set<std::string> bad_keys;
    unsigned int id_count;
    int factor;
    bool random;
    bool bad;
    std::ofstream file;
};

#endif