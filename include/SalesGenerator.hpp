#ifndef SALES_GENERATOR_HPP
#define SALES_GENERATOR_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <random>

#include "CSVEntry.hpp"
#include "Date.hpp"

class MockSale {
public:
    /* 
    * @brief Constructs a MockSale from the given Item
    * @param std::shared_ptr<CSVEntry> Item
    * @param unsigned-long ID of transaction
    */
    MockSale(std::shared_ptr<CSVEntry>, unsigned long);

    /* 
    * @brief Randomizes num_sold, and decrements the Item's quantity.
    */
    void setNumSold();

    /*
     * @brief Prints the MockSale to an ostream.
     * @param std::ostream& Output stream
    */
    void print(std::ostream&);

    std::shared_ptr<CSVEntry> item;
    unsigned long id;
    unsigned long item_id;
    unsigned long num_sold;
    double sale_price;
};

class MockTransaction {
public:
    MockTransaction(unsigned long);

    /*
     * @brief Adds a new Sale to the Transaction.
     * @param std::shared_ptr<CSVEntry> Item to add to transaction.
    */
    std::shared_ptr<MockSale> addSale(std::shared_ptr<CSVEntry>);

    /*
     * @brief Gets a random name for a buyer or seller.
     * @return std::string Name
    */
    std::string getRandomName();

    /*
     * @brief Prints the MockTransaction to an ostream.
     * @param std::ostream& Output stream
    */
    void print(std::ostream&);

    unsigned long id;
    Date date;
    double total_price;
    unsigned long quantity_of_items;
    std::string buyer;
    std::string seller;
};

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

    /*
    * @brief Generates a new transaction.
    */
    std::shared_ptr<MockTransaction> newTransaction();

    /*
     * @brief Generates # of transactions.
     * @param unsigned-long Number of transactions.
    */
    void generateTransactions(unsigned long);

protected:
    const unsigned long MAX_SALES_PER_TRANSACTION = 10;

    unsigned long transactions;
    std::string original_name;
    std::string parent_name;
    std::string child_name;
    Date last_date;
    std::vector<std::shared_ptr<CSVEntry>> inventory;
};

#endif