#ifndef INVENTORY_RANDOMIZER_HPP
#define INVENTORY_RANDOMIZER_HPP

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>

class Entry {
   public:
    Entry(std::string, std::string, std::string, std::string);
    void print(std::ofstream&);

   private:
    friend class InventoryRandomizer;
    std::string name;
    std::string category;
    std::string sub_category;
    std::string location;
    int quantity;
    int backorder;
    int id;
    double sale_price;
    double buy_cost;
    double tax;
    double total_price;
    double profit;
    std::string expiration_date;
};

class InventoryRandomizer {
   public:
    InventoryRandomizer(std::string, std::string);
    void outputFile();
    void readFile();
    void generateRandom();

   private:
    std::string input_file;
    std::string out_file;
    std::vector<std::shared_ptr<Entry>> entries;
};

#endif