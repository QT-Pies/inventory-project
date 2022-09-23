#ifndef CSVGENERATOR_HPP
#define CSVGENERATOR_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <random>
#include <memory>
#include "CSVEntry.hpp"

class CSVGenerator
{
public:
    CSVGenerator();
    void generateFile(const std::string&, unsigned int, unsigned int, unsigned int);
protected:
    std::shared_ptr<CSVEntry> generateItem();
    std::shared_ptr<CSVEntry> generateNonPerishableItem();
    std::shared_ptr<CSVEntry> generatePerishableItem();

    const std::vector<std::string> columns = {"Name", "ID", "Category", "Quantity", "Sale Price", "Tax", "Total Price", "Buy Cost", "Profit", "Expiration Date"};
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    unsigned int id_count;
    std::ofstream file;
};

#endif