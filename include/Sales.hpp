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
   * Sale constructor that sets all the data for the given sale
   * Sale deconstructor is empty since smart pointers are used
   * Note it is checked at some point that most the numbers are not 0 and
   * strings are not empty.
   */
  Sale(const unsigned long, const unsigned long, const std::string&,
       const unsigned long, const double, const double, const std::string&,
       const std::string&);
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

class SaleList {
 public:
  /*
   * Constructor, will take in the name of the file that the sales List will be
   * working from.
   */
  SaleList(const std::string&);

  /*
   * Adds a sale to the vector by using the Sale class constructor, returns
   * false if an error occurs These errors include certain numbers being 0 or
   * strings being empty.
   */
  bool addSale(const unsigned long, const unsigned long, const std::string&,
               const unsigned long, const double, const double,
               const std::string&, const std::string&);

  /*
   * Creates a new File with the given file name, will add the begining csv
   * header for what data is being stored.
   */
  bool newFile();

  /*
   * Loads file information from the given file and enters it into the vector,
   * calls addSale.
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
