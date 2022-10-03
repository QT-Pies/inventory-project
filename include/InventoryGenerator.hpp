#ifndef INVENTORYGENERATOR_HPP
#define INVENTORYGENERATOR_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <random>
#include <memory>
#include "CSVEntry.hpp"

class InventoryGenerator
{
public:
    InventoryGenerator();
    void generateFile(const std::string&, unsigned int, unsigned int, unsigned int);
    void setBadKey(const std::string&);
    void setRandomFactor(const int&);
    void toggleRandom();
protected:
    std::shared_ptr<CSVEntry> generateItem();
    std::shared_ptr<CSVEntry> generateNonPerishableItem();
    std::shared_ptr<CSVEntry> generatePerishableItem();
    bool isBadKey(const std::string&);

    const std::vector<std::string> columns = {"Name", "ID", "Category", "Sub-Category", "Quantity", "Sale Price", "Tax", "Total Price", "Buy Cost", "Profit", "Expiration Date"};
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::set<std::string> bad_keys;
    unsigned int id_count;
    int factor;
    bool random;
    bool bad;
    std::ofstream file;
};

#endif