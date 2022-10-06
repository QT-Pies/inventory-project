#ifndef SALES_HPP
#define SALES_HPP

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "Item.hpp"

class Sale
{
friend class SaleList;
public:
    /*
     * Sale constructor that sets all the data for the given sale
     * Sale deconstructor is empty since smart pointers are used
     * Note it is checked at some point that most the numbers are not 0 and strings are not empty.
     * @param unsigned-long ID
     * @param unsigned-long Sale number
     * @param string Date of sale
     * @param unsigned-long Amount sold in transaction
     * @param double Sale subtotal
     * @param double Sales tax
     * @param string Buyer
     * @param string Seller
     */
    Sale(const unsigned long, const unsigned long, const std::string&, const unsigned long, const double, const double, const std::string&, const std::string&);

    /* Destructor; does nothing */
    ~Sale();
protected:
    unsigned long identification;
    unsigned long sale_number;
    std::string date;
    unsigned long amount_sold;
    double sale_price;
    double tax;
    std::string buyer;
    std::string seller;
    double total_price;
};

class SaleList
{
public:

    /*
     * Constructor; creates list of sales from given file.
     * @param string Name of file
     */
    SaleList(const std::string&);

    /*
     * Adds a sale to the vector by using the Sale class constructor, returns false if an error occurs
     * These errors include certain numbers being 0 or strings being empty.
     * @param unsigned-long ID
     * @param unsigned-long Sale number
     * @param string Date of sale
     * @param unsigned-long Amount sold in transaction
     * @param double Sale subtotal
     * @param double Sales tax
     * @param string Buyer
     * @param string Seller
     */
    bool addSale(const unsigned long, const unsigned long, const std::string&, const unsigned long, const double, const double, const std::string&, const std::string&);
    
    /*
     * Creates a new File with the given file name, will add the begining csv header for what data is being stored.
     */
    bool newFile();

    /* 
    * Reads in information from given file and holds it in the sales vector
    * If addSale returns false, then an error occured and false is returned.
    */
    bool load();

    /*
     * Appends to the given File and adds any new sales.
     * This assumes that once a sale is finalized it cannot be deleted
     * and uses an offset that will be set previously to keep track of new sales.
     */
    bool save();
protected:
    std::vector<std::shared_ptr<Sale> > sales;
    std::string file_name;
    int offset;
};

#endif