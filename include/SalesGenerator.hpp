#ifndef SALES_GENERATOR_HPP
#define SALES_GENERATOR_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <random>

#include "CSVEntry.hpp"

class SalesGenerator {
public:
    SalesGenerator(const std::string&);
    
    /* 
    * @brief Reads the inventory file in.
    * @brief Does not error check inventory -- pass a valid file.
    * @param std::string Name of file to open
    * @return true if nothing went wrong, false if error encountered
    */
    bool readInventory();

    /* 
     * @brief Returns a random item from the inventory to add to the transaction.
    */
    std::shared_ptr<CSVEntry> grabRandomItem();

protected:
    std::string original_name;
    std::string parent_name;
    std::string child_name;
    std::vector<std::shared_ptr<CSVEntry>> inventory;
};

#endif