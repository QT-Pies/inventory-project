#ifndef SALES_HPP
#define SALES_HPP

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Item.hpp"

class Sale {
    friend class SaleList;

   public:
    /*
     * @brief Sale constructor that sets all the data for the given sale.
     * Note it is checked at some point that most the numbers are not 0 and
     * strings are not empty.
     * @param unsigned-long ID
     * @param unsigned-long Sale number
     * @param string Date of sale
     * @param unsigned-long Amount sold in transaction
     * @param double Sale subtotal
     * @param double Sales tax
     * @param string Buyer
     * @param string Seller
     */
    // 10 parameters lol, this is really redundant, might want to make sale just about the cild file, then sale list with parent file
    // sale_id | num_items | 
    Sale(const unsigned long, const unsigned long, const std::string&, const unsigned long, const double, const double,
         const std::string&, const std::string&);

    /* @brief Destructor; does nothing */
    ~Sale();

   protected:
    // variables for both
    unsigned long sale_id;
    // variables for parent
    unsigned long num_items;
    // variables used for child file
    unsigned long item_id, quantity_sold;
    double sale_price;
};

class SaleList {
   public:
    /*
     * @brief Constructor; creates list of sales from given file.
     * @param std::string Name of file
     */
    SaleList();
    bool addSale(const unsigned long, const unsigned long, const std::string&, const unsigned long, const double,
                 const double, const std::string&, const std::string&);

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

   protected:
   // will change this data structure, want to impliment a bit first
    std::vector<std::shared_ptr<Sale> > sales;
    std::string parent_file, child_file;
    int offset;
};

#endif