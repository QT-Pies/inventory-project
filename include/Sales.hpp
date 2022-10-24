#ifndef SALES_HPP
#define SALES_HPP

#include <stdio.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Date.hpp"
#include "Item.hpp"

class Sale {
   public:
    /*
     * @brief Sale constructor that sets all the data for the given sale.
     * @param unsigned long saleID
     * @param unsigned long itemID
     * @param unsigned long Amount of items sold in sale
     * @param unsigned long Sale Price of item when sale is made
     */
    Sale(const unsigned long, const unsigned long, const unsigned long, const double);

    /* @brief Destructor; does nothing */
    ~Sale();

   private:
    friend class Transaction;
    friend class SaleList;

   protected:
    unsigned long sale_id, item_id, num_sold;
    double sale_price;
    std::string unique_sale_id;
};

class Transaction {
   public:
    /*
     * @brief Transaction constructor that sets all the data for the given transaction.
     * @param unsigned long saleID
     * @param std::string Buyer
     * @param std::string Seller
     * @param unsigned int Year sale is made
     * @param unsigned int Month sale is made
     * @param unsigned int Day sale is made
     */
    Transaction(const unsigned long, const std::string, const std::string, const unsigned int, const unsigned int,
                const unsigned int);

    /* @brief Destructor; does nothing */
    ~Transaction();

    /*
     * @brief Adds a sale to the transaction and stores it in the sales vector
     * @param unsigned long saleID
     * @param unsigned long itemID
     * @param unsigned long Amount of items sold in sale
     * @param unsigned long Sale Price of item when sale is made
     * returns true if added, false if failed
     */
    bool addSale(const unsigned long, const unsigned long, const unsigned long, const double);

    /*
     * @brief removes a sale from the transaction and makes the ptr NULL in the vector
     * @param unsigned long saleID
     * @param unsigned long itemID
     * @param unsigned long Amount of items sold in sale
     * @param unsigned long Sale Price of item when sale is made
     * @return true if removed, false if sale was not found
     */
    bool removeSale(const unsigned long, const unsigned long, const unsigned long, const double);

   private:
    friend class SaleList;

   protected:
    unsigned long sale_id, num_sales;
    unsigned int year, month, day;
    double total_price;
    std::string buyer, seller, date, unique_transaction_id;
    std::vector<std::shared_ptr<Sale> > sales;
};

class SaleList {
    friend class InventoryManager;

   public:
    SaleList();
    ~SaleList();

    /*
     * @brief Adds a new transaction based on user input, date is set based on current day
     * @param unsigned long saleID
     * @param std::string Buyer
     * @param std::string Seller
     * @param unsigned int Year sale is made
     * @param unsigned int Month sale is made
     * @param unsigned int Day sale is made
     */
    void userTransaction(const unsigned long, const std::string, const std::string);

    /*
     * @brief Adds a new transaction based on the sales file or on a call by userTransaction
     * @param unsigned long saleID
     * @param std::string Buyer
     * @param std::string Seller
     * @param unsigned int Year sale is made
     * @param unsigned int Month sale is made
     * @param unsigned int Day sale is made
     */
    void newTransaction(const unsigned long, const std::string, const std::string, const unsigned int,
                        const unsigned int, const unsigned int);

    /*
     * @brief Reads in information from given file's parent and child
     * sales files and stores it in appropriate places.
     * Will also set current sale ID. This resets at 1 every day, if there are sales
     * from earlier in the day it will be set appropriatly.
     * @return true on success, false on failure
     */
    bool loadSales(const std::string);

    /*
     * @brief Writes to the given Files and adds all sales and transactions
     * to the child and parent files respectively
     * @return true on success, false on failure
     */
    bool save();

    /* @brief Prints out all of the transactions in order from oldest to newest */
    void print();

   protected:
    std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, std::shared_ptr<Transaction> > > >
        transaction_by_date;
    std::vector<std::shared_ptr<Transaction> > transaction_by_order;
    std::string parent_file, child_file;
    unsigned int curr_transaction;  // is place of the last element in transaction by order
    unsigned long curr_sale_id;     // is the current saleID for the given day
};

#endif