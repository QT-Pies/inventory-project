#ifndef SALES_HPP
#define SALES_HPP

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>

#include "Item.hpp"

class Sale {
    friend class SaleList;

   public:
    /*
     * @brief Sale constructor that sets all the data for the given sale.
     * Note it is checked at some point that most the numbers are not 0 and
     * strings are not empty.
     */
    // sale_id | item_id | num_sold | sale_price
    Sale(const unsigned long, const unsigned long, const unsigned long, const double);

    /* @brief Destructor; does nothing */
    ~Sale();

   protected:
    unsigned long sale_id, item_id, num_sold;
    double sale_price;
};

class Transaction {
    friend class SaleList;

   public:
   // sale_id | buyer | seller | 
    Transaction(const unsigned long, const std::string, const std::string, const std::string);
    ~Transaction();
    // will call sale constructor with these 
    bool add_sale(const unsigned long, const unsigned long, const unsigned long);
    // will calculate total_price and set num_sales appropriatly, tax will be hard coded at .0635, average in us
    // will want to change tax appropriatly, maybe add tax break feture to
    // date will be set with automatically as well, baised on current day or file reading

   protected:
    int sale_id, num_sales;
    double total_price;
    std::string date, buyer, seller;
    std::vector<std::shared_ptr<Sale> > sales;

};

class SaleList {
   public:
    /*
     * @brief Constructor; creates list of sales from given file.
     * @param std::string Name of file
     */
    SaleList();
    // will call Transaction constructor
    bool add_transaction(const unsigned long, const std::string, const std::string, const std::string);

    /*
     * @brief Creates a new File with the given file name, will add the begining
     * CSV header for what data is being stored.
     * @return true on success, false on failure
     */
    bool newFile();

    /*
     * @brief Reads in information from given file and holds it in the sales
     * vector. If addSale returns false, an error occurred.
     * @return true on success, false on failure
     */
    bool load();

    /*
     * @brief Appends to the given File and adds any new sales.
     * This assumes that once a sale is finalized it cannot be deleted
     * and uses an offset that will be set previously to keep track of new sales.
     * @return true on success, false on failure
     */
    bool save();
    // prints all transactions
    void print();

   protected:
    // will change this data structure, want to impliment a bit first
    // std::vector<std::shared_ptr<Sale> > sales;
    // year, month, day, then 
    std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, std::shared_ptr<Transaction> > > > transaction_by_date;
    std::string parent_file, child_file;
};

#endif

// in constructor, initilizes maps of sales and transactions, so I dont have to worry about 

// search by day, return just the day
// should also do month and year, returning the respectice maps

// have (S) take in a full transaction, first check to see if files are open, and have correct starting format, if empty create new file, else load, 
// have a check to seee if previously loaded, maybe just see if its empty or not
// take in sales, maybe until a particular string is read in, then after save to file, not append
// also